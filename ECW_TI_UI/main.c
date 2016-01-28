#include <stdint.h>
#include "driverlib.h"
#include "grlib.h"
#include "LcdDriver/Dogs102x64_UC1701.h"
#include "stdio.h"
#include "math.h"
#include <stdint.h>
#include "msp430.h"
#include "HAL_Buttons.h"
#include "HAL_Board.h"
#include "HAL_Dogs102x6.h"
#include "HAL_Wheel.h"

#define lcd_clear() GrClearDisplay(&g_sContext);
#define N 100;

//286 bytes of ram in use

//global variables

uint16_t timeoutCounter;
tContext g_sContext;
tRectangle g_sRect;
int32_t stringWidth = 0;

//Back end variables
float  AdcThreshold=255,temp=0;
float  FThreshold,tempF=0;
float  X;
float  dcval=0;
int    fourier_offset=0;
unsigned int eeprom_address;
short  input;     //on pin 6.6
short  ON=0,calibrated_adc=0,calibrated_steady=0,calibrated_F=0,menu_counter;
short  i=0;
short  small_blink=0,big_blink=0,steady_trough=255,steady_crest=0,trough=0,crest=0,max_input=0,view_counter=0;
short  temp_BigB=0,counter_BigB=0;

//UI variables
int menu=0,option=0,exec_counter=0;
int max_menu=5;
int total_options[]={4,4,5,6,2};
int disp_counter=1;

//function declarations
void Clock_init(void);
void Delay(void);
void switch_init();
void lcd_init();
void adc_init();
int adc_read();
void delay_us(int us);
void delay_ms(int ms);
void delay_s(int s);
void eeprom_write_bytes(char* bytes, unsigned int num_bytes);
char eeprom_read_byte(unsigned int address);
void set_up();
void bot_StartStop();
float dft();
void check_blink();
void check_fourier_offset();


//function definitions
void Clock_init(void)
{
	UCS_setExternalClockSource(
                               32768,
                               0);

    // Set Vcore to accomodate for max. allowed system speed
    PMM_setVCore(
    		PMM_CORE_LEVEL_3
                );

    // Use 32.768kHz XTAL as reference
    UCS_LFXT1Start(
        UCS_XT1_DRIVE0,
        UCS_XCAP_3
        );


    // Set system clock to max (25MHz)
    UCS_initFLLSettle(
    	25000,
        762
        );

    SFR_enableInterrupt(
                        SFR_OSCILLATOR_FAULT_INTERRUPT
                       );

    // Globally enable interrupts
    __enable_interrupt();
}


void Delay(void)
{
	__delay_cycles(SYSTEM_CLOCK_SPEED );
}

void switch_init(){
	 __enable_interrupt();

	 Buttons_init(BUTTON_S1 );
	 Buttons_interruptEnable(BUTTON_S1 );

	 Buttons_init(BUTTON_S2 );
	 Buttons_interruptEnable(BUTTON_S2 );
}

void lcd_init(){
	Dogs102x64_UC1701Init();
	GrContextInit(&g_sContext, &g_sDogs102x64_UC1701);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
	GrClearDisplay(&g_sContext);
}

void adc_init()
{
    ADC12CTL0 = ADC12SHT0_9|ADC12ON;       // Sampling time, ADC12 on
    ADC12CTL1 = ADC12SHP;                  // Use sampling timer
    ADC12MCTL0 = ADC12INCH_6;
    ADC12CTL0 |= ADC12ENC;
    P6SEL |= BIT6 ;                        // P6.6 ADC option select
    ADC12CTL0 &= ~ADC12SC;                 // Clear the ADC start bit

    /*//ADC pin 6.6
        ADC12CTL0 = ADC12SHT0_9|ADC12ON;       // Sampling time, ADC12 on
        ADC12CTL1 = ADC12SHP;                     // Use sampling timer
        ADC12MCTL0 = ADC12INCH_6;
        ADC12CTL0 |= ADC12ENC;
        P6SEL |= BIT6 ;                            // P6.6 ADC option select
        // Set conversion mem control register ADC12MCTL0 = 0001 0000
        // EOS = 0, SREF =001 -->Voltage refs = GND to (Vref+)
        // INCHx = 0000 = analog input from A0
        ADC12MCTL0 =  ADC12INCH_6;
        ADC12CTL0 &= ~ADC12SC;
        //Enable and start (single) conversion (not using ADC int)
        ADC12CTL0 |= ADC12SC + ADC12ENC;*/
}

int adc_read()
{
    ADC12CTL0 |= ADC12SC + ADC12ENC;       // Start sampling/conversion
    while (ADC12CTL1 & ADC12BUSY);         // Wait until conversion is complete
    return (ADC12MEM0 & 0x0FFF)/16;             // Mask 4 upper bits of ADC12MEM0(12 bit ADC); div by 16 for 8 bit adc
}

void _delay_us(int us)
{
    while(us --) __delay_cycles(1);
}

void _delay_ms(int ms)
{
    while(ms --) __delay_cycles(1087);
}

void _delay_s(int s)
{
    while(s --) __delay_cycles(1086957);
}

void eeprom_write_bytes(char* bytes, unsigned int num_bytes)
{
  char *Flash_ptr;                          // Initialize Flash pointer
  Flash_ptr = (char *) 0x1880;
  __disable_interrupt();
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+ERASE;                      // Set Erase bit
  *Flash_ptr = 0;                           // Dummy write to erase Flash seg
  FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation
  unsigned int i;
  for(i = 0 ; i < num_bytes ; ++ i)
      *Flash_ptr++ = bytes[i];              // Write value to flash
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit
  __enable_interrupt();
}

char eeprom_read_byte(unsigned int address)
{
  char *Flash_ptr;                          // Initialize Flash pointer
  Flash_ptr = (char *) 0x1880;
  FCTL3 = FWKEY;
  char byte = Flash_ptr[address];
  FCTL3 = FWKEY + LOCK;
  return byte;
}

void set_up(){
     // Stop WDT
     WDT_A_hold(WDT_A_BASE);

     // Basic GPIO initialization
     Board_init();
     Clock_init();

     // Set up LCD
     lcd_init();

     print_string(22,30,"*WELCOME*");
     Delay();

     //Buttons S1 S2
	 switch_init();

	 //PORTD=0xFF;
	 //adc 6.6 pin
	 adc_init();
	 //DDRC=0XFF;

	 eeprom_address=0x0000;
	 AdcThreshold=eeprom_read_byte(eeprom_address);
	 eeprom_address++;
	 dcval=eeprom_read_byte(eeprom_address);
	 eeprom_address++;
	 fourier_offset=eeprom_read_byte(eeprom_address);
	 eeprom_address=0x10;
	 FThreshold=eeprom_read_byte(eeprom_address);

	 //usart_init();
	 //pwm_init();

}

void bot_StartStop(){
     if(ON){
		 lcd_clear();
		 print_string(50,30,"stop");
		 bot_stop();
		 _delay_ms(1000);
		 lcd_clear();
		 ON=0;
	 }
	  else if(!ON){
		 lcd_clear();
		 print_string(50,30,"start");
		 _delay_ms(1500);     //will move forward for minimum 500 ms till told to stop
		 bot_forward();
		 lcd_clear();
		 ON=1;
	 }
}

float dft(){
     int Ns=100;
     int n,k,data[100];
     float ReX,ImX,Xl;

	 for(k=0;k<Ns;k++){ //sample data with frequency Fs
		 data[k] = adc_start(0);    // read the input pin
		 _delay_us(900);    //Ts=10e5/N usec
	 }

	 k=1;
	 ReX=0;
	 ImX=0;
	 for(n=0;n<Ns;n++){               //DFT
		 ReX=ReX+cos(2*3.14*n*k/Ns)*data[n]*0.01;
		 ImX=ImX+sin(2*3.14*n*k/Ns)*data[n]*0.01;
	 }
         //this is only to compute the max sample value;remove if not needed
		 temp_BigB=0;
		 counter_BigB=0;
         for(n=0;n<100;n++){
                 if(max_input<data[n]) max_input=data[n];
				 /*if(data[n]>70) {//when noise level of big blink remains above this level
				     temp_BigB++;
					 if(temp_BigB>counter_BigB)//store max count
					     counter_BigB=temp_BigB;//store before reset
				 }
				 else temp_BigB=0;//reset as normally spikes go above and below*/
         }

         //compute the magnitude
	 Xl=(ReX*ReX+ImX*ImX);

	 return Xl;

}

void check_blink(){
         max_input=0;
         X=dft();
         if(X>FThreshold){
             if(max_input>86)  big_blink=1; //see the max adc val corresssponding to saturation output of eog ckt
		     //if(X>400)  big_blink=1;//big blink fourier value;same values for small and big blink
		     //if(counter_BigB>7) big_blink=1;//arbitrary counter
		     else
                 small_blink=1;
         }

}

void check_fourier_offset(){
        X=dft();
        if(X>fourier_offset){ //typecast if needed
                fourier_offset=X;
        }
}


void highlight_and_print_string(int column,int row,char *s){
    GrContextForegroundSet(&g_sContext, ClrWhite);
    GrContextBackgroundSet(&g_sContext, ClrBlack);

    GrStringDraw(&g_sContext,
    		s,
    		AUTO_STRING_LENGTH,
    		column,
    		row,OPAQUE_TEXT);
}

void print_string(int column,int row,char *s){
    GrContextForegroundSet(&g_sContext, ClrBlack);
    GrContextBackgroundSet(&g_sContext, ClrWhite);

    GrStringDraw(&g_sContext,
    		s,
    		AUTO_STRING_LENGTH,
    		column,
    		row,OPAQUE_TEXT);
}

void print_int(int column,int row,int n){
    GrContextForegroundSet(&g_sContext, ClrBlack);
    GrContextBackgroundSet(&g_sContext, ClrWhite);

    char s[10];
    snprintf(s,10,"%d",n);

    GrStringDraw(&g_sContext,
    		s,
    		AUTO_STRING_LENGTH,
    		column,
    		row,TRANSPARENT_TEXT);
}




void plot(){
	unsigned int sample1,sample2,i=0;
    buttonsPressed=0;

    Dogs102x6_init();
    Dogs102x6_backlightInit();
    Dogs102x6_setBacklight(11);
    Dogs102x6_setContrast(11);
    Dogs102x6_clearScreen();

    Dogs102x6_stringDraw(7, 0, "*S2=Esc*", DOGS102x6_DRAW_NORMAL);
    while(1)
    {
    	if(buttonsPressed){
    	      buttonsPressed=0;
    	      lcd_init(); //initialise grlib
    	      break;
    	 }
          if(i == 101)
          {
              Dogs102x6_clearScreen();
              Dogs102x6_stringDraw(7, 0, "*S2=Esc*",DOGS102x6_DRAW_NORMAL);
              i = 0;
           }
           ADC12CTL0 |= ADC12SC + ADC12ENC;
           // Start sampling/conversion
           while (ADC12CTL1 & ADC12BUSY) __no_operation();
           sample1 = ADC12MEM0 & 0x0FFF;
           __delay_cycles(1000000);
           ADC12CTL0 |= ADC12SC + ADC12ENC;
           // Start sampling/conversion
           while (ADC12CTL1 & ADC12BUSY) __no_operation();
           sample2 = ADC12MEM0 & 0x0FFF;
           Dogs102x6_lineDraw(i,56-sample1/86,i+1,56-sample2/86,0);
           /*if(buttonsPressed && BUTTON_S1)
           {
               buttonsPressed = 0;
               while(!(buttonsPressed && BUTTON_S1));
               buttonsPressed = 0;
           }*/
           ++ i;


      }
}



void main(void)
{
    set_up();

    buttonsPressed = 0;
    while(1){

    	exec_counter=0;
    	//to select menu
    	if (buttonsPressed & BUTTON_S2){
    		if(menu==0) {
    			menu=option+1;
    			option=0;
    		}
    		else exec_counter=1;
    		disp_counter=1;
    		buttonsPressed = 0;
    	}

    	//to scroll options
    	if (buttonsPressed & BUTTON_S1){
    		if(option<(total_options[menu]-1)){
    			option++;
    		}
    		else option=0;
    		disp_counter=1;
    	    buttonsPressed = 0;
    	    	}

        if(disp_counter==1){
        	disp_counter=0;//to prevent  writing if no change
        	GrClearDisplay(&g_sContext);
        	switch(menu){
        	case 0:
        		print_string(0,0,"=====Menu====");
        		print_string(0,8,"1.Calibrate");
        		print_string(0,16,"2.View Thresholds");
        		print_string(0,24,"3.Enable Eye ");
        		print_string(0,32,"4.View Signal");
        		switch(option){
        		case 1:
        			highlight_and_print_string(0,16,"2.View Thresholds");
        			break;

        		case 2:
        			highlight_and_print_string(0,24,"3.Enable Eye ");
        			break;

        		case 3:
        			highlight_and_print_string(0,32,"4.View Signal");
        			break;

        		default:
        			highlight_and_print_string(0,8,"1.Calibrate");
        			option=0;
        			break;
        		}
        		break;

        	case 1:
        		print_string(0,0,"===Calibrate===");
        		print_string(0,8,"1.Steady Values");
        		print_string(0,16,"2.Peak");
        		print_string(0,24,"3.Fourier ");
        		print_string(0,32,"4.Back");
        		switch(option){
        		case 1:
        			highlight_and_print_string(0,16,"2.Peak");
        			if(exec_counter==1){
        				exec_counter=0;
        				lcd_clear();
        				 //to calibrate small blink adc Thresholds;cannot view adc values till out
        								 while(!(buttonsPressed & BUTTON_S2)){
        								 if(calibrated_adc==0) {
        								         AdcThreshold=255;
        										 lcd_clear();
        										 print_string(0,0,"Blink to calibrate");
        										 print_string(56,0,"*S2=ESC*");
        										 _delay_ms(1000);
        										 lcd_clear();
        								 }
        								 temp = adc_read();
        								 _delay_ms(20);
        								 crest=0;
        							     // to check crest
        								 while(temp<adc_read()){
        									 temp = adc_read();
        									 _delay_ms(20);
        									 crest=1;
        								 }
        								 if(crest && temp>steady_crest && temp<AdcThreshold){
        									 AdcThreshold=temp;
        								 }
        								 calibrated_adc=1;
        								 lcd_clear();
										// print_string(0,0,"Blink to calibrate");
										 //print_string(56,0,"*S2=ESC*");
        								 print_int(50,30,AdcThreshold);
        								 _delay_ms(100);
        									 }

        								 if(AdcThreshold==255) AdcThreshold=steady_crest;//if 50 hz noise
        								 lcd_clear();

        								 buttonsPressed=0;
        								 disp_counter=1;

        			}
        			break;

        		case 2:
        			highlight_and_print_string(0,24,"3.Fourier Threshold");
        			break;

        		case 3:
        			highlight_and_print_string(0,32,"4.Back");
        			if(exec_counter==1){
        				menu=0;
        				option=0;
        				disp_counter=1;
        			}
        			break;

        		default:
        			highlight_and_print_string(0,8,"1.Steady Values");
        			option=0;
        			break;
        		}
        		break;

        	case 2:
        		print_string(0,0,"===Thresholds===");
        		print_string(0,8,"1.DC");
        		print_string(0,16,"2.Steady Peak");
        		print_string(0,24,"3.Peak");
        		print_string(0,32,"4.Fourier Threshold");
        		print_string(0,40,"5.Back");
        		switch(option){
        		case 1:
        			highlight_and_print_string(0,16,"2.Steady Peak");
        			break;

        		case 2:
        			highlight_and_print_string(0,24,"3.Peak");
        			break;

        		case 3:
        			highlight_and_print_string(0,32,"4.Fourier Threshold");
        			break;

        		case 4:
        			highlight_and_print_string(0,40,"5.Back");
        			if(exec_counter==1){
        				menu=0;
        				option=0;
        				disp_counter=1;
        			}
        			break;

        		default:
        			highlight_and_print_string(0,8,"1.DC");
        			option=0;
        			break;
        		}
        		break;
        	case 3:
        		print_string(0,0,"===Eye Control===");
        		print_string(0,8,"1.Wait");
        		print_string(0,16,"2.Left");
        		print_string(0,24,"3.Right");
        		print_string(0,32,"4.Forward");
        		print_string(0,40,"5.Backward");
        		print_string(0,48,"6.Main menu");
        		switch(option){
        		case 1:
        			highlight_and_print_string(0,16,"2.Left");
        			break;

        		case 2:
        			highlight_and_print_string(0,24,"3.Right");
        			break;

        		case 3:
        			highlight_and_print_string(0,32,"4.Forward");
        			break;

        		case 4:
        			highlight_and_print_string(0,40,"5.Backward");
        			if(exec_counter==1){
        				menu=0;
        				disp_counter=1;
        			}
        			break;

        		case 5:
        			highlight_and_print_string(0,48,"6.Main Menu");
        			if(exec_counter==1){
        				menu=0;
        				option=0;
        				disp_counter=1;
        			}
        			break;

        		default:
        			highlight_and_print_string(0,8,"1.Wait");
        			option=0;
        			break;
        		}
        		break;
        	case 4:
        		print_string(0,0,"S1 pause/resume");
        		print_string(0,56,"S2 Back");
        		plot();
    		    menu=0;option=0;
    		    disp_counter=1;
        		break;
        	default:break;
        	}
        }
    }


}

