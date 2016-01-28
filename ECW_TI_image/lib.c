/*
 * lib.c
 *
 *  Created on: 22-Feb-2015
 *      Author: Anson
 */
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

//function declarations
void eye_control();
void bot_stop();
void bot_forward();
void bot_backward();
void bot_left();
void bot_right();
void Clock_init(void);
void Delay(void);
void switch_init();
void lcd_init();
void Dogs_lcd_init();
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
void Dogs_print_int(int column, int row,int n);
void highlight_and_print_string(int column,int row,char *s);
void print_string(int column,int row,char *s);
void print_int(int column,int row,int n);
void plot();

uint16_t timeoutCounter;
tContext g_sContext;

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
short  temp_BigB=0,counter_BigB=0,max_slope=0,diff,BB_flag;


void switch_init(){
	 __enable_interrupt();

	 Buttons_init(BUTTON_S1 );
	 Buttons_interruptEnable(BUTTON_S1 );

	 Buttons_init(BUTTON_S2 );
	 Buttons_interruptEnable(BUTTON_S2 );
}

void eye_control(){
    while(1){
		 if(buttonsPressed & BUTTON_S2){   //D3 to disable eye control
			 bot_stop();
			 buttonsPressed=0;
			 lcd_clear();
			 print_string(40,30,"Disabled!!");
			 _delay_ms(3000);
			 lcd_clear();
			 break;
		 }

        small_blink=0,big_blink=0,ON=0,menu_counter=0;
		 short toggle=1;
		 input = adc_read();

         highlight_and_print_string(0,8,"1.Waiting...");
         _delay_ms(100);
		 // lcd_clear();

		 if(input > AdcThreshold || input==AdcThreshold){
		        check_blink();
		 }

		 if(big_blink){
		     _delay_ms(1000);
			 while(1){
				 if(buttonsPressed & BUTTON_S2){   //D3 to disable eye control
					 bot_stop();
					 /*lcd_clear();
					 print_string(24,30,"Disabled!!");
					 _delay_ms(1000);
					 lcd_clear();*/
					 break;
				 }
				 small_blink=0,big_blink=0;
				 input = adc_read();
				 if(input > AdcThreshold){
					 check_blink();
				 }
				 if(small_blink && !ON){
					 menu_counter++;
					 toggle=1;
					 if(menu_counter==5) menu_counter=0;

				 }


				else if(big_blink){
						//lcd_clear();
						if(ON){
							   ON=0;
							   bot_stop();
							   _delay_ms(1000);
							   toggle=1;
						}
						else if(menu_counter==0){
						       _delay_ms(1000);
							   break;
						}
						else if(menu_counter==1){
							   highlight_and_print_string(0,16,"2.Left...");
							   _delay_ms(1000);
							   bot_left();
							   ON=1;
						}
						else if(menu_counter==2){
							   highlight_and_print_string(0,24,"3.Right...");
							   _delay_ms(1000);
							   bot_right();
							   ON=1;
						}
						else if(menu_counter==3){
						    	highlight_and_print_string(0,32,"4.Forward...");
							   _delay_ms(1000);
							   bot_forward();
							   ON=1;
						}
						else if(menu_counter==4){
						    	highlight_and_print_string(0,40,"5.Backward...");
							   _delay_ms(1000);
							   bot_backward();
							   ON=1;
						}


				}


				if(!ON && toggle){
					 toggle=0;
					 //lcd_clear();
		             print_string(0,0,"===Eye Control===");
		             print_string(0,8,"1.Wait      ");
		        	 print_string(0,16,"2.Left   ");
		        	 print_string(0,24,"3.Right   ");
		             print_string(0,32,"4.Forward   ");
		        	 print_string(0,40,"5.Backward   ");
		        	 print_string(0,56,"*S2=ESC*");

					 switch(menu_counter){
					 case 0:
			              highlight_and_print_string(0,8,"1.Wait      ");
						 _delay_ms(100);
						 break;
					 case 1:
						  highlight_and_print_string(0,16,"2.Left   ");
						 _delay_ms(100);
						 break;
					 case 2:
						 highlight_and_print_string(0,24,"3.Right   ");
						 _delay_ms(100);
						 break;
					 case 3:
						 highlight_and_print_string(0,32,"4.Forward   ");
						 _delay_ms(100);
						 break;
					 case 4:
						 highlight_and_print_string(0,40,"5.Backward   ");
						 _delay_ms(100);
						 break;
				   default:
						 break;
				  }
				}
			}
		}


	 }
}

void bot_stop(){

}

void bot_forward(){

}

void bot_backward(){

}

void bot_left(){

}

void bot_right(){

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

	 eeprom_address=0;
	 AdcThreshold=eeprom_read_byte(eeprom_address);
	 eeprom_address++;
	 dcval=eeprom_read_byte(eeprom_address);
	 eeprom_address++;
	 steady_crest=eeprom_read_byte(eeprom_address);
	 eeprom_address++;
	 fourier_offset=eeprom_read_byte(eeprom_address);
	 eeprom_address++;
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
		 data[k] = adc_read();    // read the input pin
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
		 max_input=0;
		 max_slope=0;
         for(n=0;n<100;n++){
                 if(max_input<data[n]) max_input=data[n];

                 //to check max_slope
                 diff=data[n+1]-data[n];
				 /*if(data[n]>70) {//when noise level of big blink remains above this level
				     temp_BigB++;
					 if(temp_BigB>counter_BigB)//store max count
					     counter_BigB=temp_BigB;//store before reset
				 }
				 else temp_BigB=0;//reset as normally spikes go above and below*/
         }

    	 //to check max_slope
         for(n=0;n<100-20;n++){
             diff=abs(data[n+20]-data[n]);
             if (diff>max_slope){
            	 max_slope = diff;
             }
         }

         //compute the magnitude
	 Xl=(ReX*ReX+ImX*ImX);

	 return Xl;

}

void check_blink(){
         max_input=0;
         BB_flag=0;
         X=dft();
         if(X>FThreshold){
        	 if(ON /*&& max_input>110*/){
        		 big_blink=1;
        	 }
        	 else if(max_input>120){//see the max adc val corresssponding to saturation output of eog ckt
            	 for(i=0;i<4;i++){
            		 X=dft();
            		 if(max_input>100 || max_slope>30){
            			 BB_flag++;
            		 }

            	 }
                 if(BB_flag>0){
                		 big_blink=1;
                 }
            	 else
            	     small_blink=1;
        	 }
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

void Dogs_print_int(int column, int row,int n){
	char s[10];
	snprintf(s,10,"%d",n);
	Dogs102x6_stringDraw(column, row, s, 0x00);
}




void plot(){
	unsigned int sample1,sample2,i=0;
    buttonsPressed=0;

    Dogs_lcd_init();

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

void lcd_init(){
	Dogs102x64_UC1701Init();
	GrContextInit(&g_sContext, &g_sDogs102x64_UC1701);
	GrContextForegroundSet(&g_sContext, ClrBlack);
	GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
	GrClearDisplay(&g_sContext);
}

void Dogs_lcd_init(){
    Dogs102x6_init();
    Dogs102x6_backlightInit();
    Dogs102x6_setBacklight(11);
    Dogs102x6_setContrast(11);
    Dogs102x6_clearScreen();
}


