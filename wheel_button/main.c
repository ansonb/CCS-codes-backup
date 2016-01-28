#include <stdint.h>
#include "driverlib.h"
#include "grlib.h"
#include "LcdDriver/Dogs102x64_UC1701.h"
#include "stdio.h"
#include <stdint.h>
#include "msp430.h"
#include "HAL_Buttons.h"
#include "HAL_Board.h"
#include "HAL_Dogs102x6.h"
#include "HAL_Wheel.h"



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


uint16_t timeoutCounter;
tContext g_sContext;
tRectangle g_sRect;

int32_t stringWidth = 0;

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

//global variables
unsigned int sample1,sample2,i=0;
int menu=0,option=0,exec_counter=0;
int max_menu=5;
int total_options[]={4,4,5,6,2};
int disp_counter=1;


void plot(){
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
    	      Dogs102x64_UC1701Init();
    	      GrContextInit(&g_sContext, &g_sDogs102x64_UC1701);
    	      GrContextForegroundSet(&g_sContext, ClrBlack);
    	      GrContextBackgroundSet(&g_sContext, ClrWhite);
    	      GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
    	      GrClearDisplay(&g_sContext);
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

void set_up(){
    // Stop WDT
    WDT_A_hold(WDT_A_BASE);

    // Basic GPIO initialization
    Board_init();
    Clock_init();

    // Set up LCD
    Dogs102x64_UC1701Init();
    GrContextInit(&g_sContext, &g_sDogs102x64_UC1701);
    GrContextForegroundSet(&g_sContext, ClrBlack);
    GrContextBackgroundSet(&g_sContext, ClrWhite);
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
    GrClearDisplay(&g_sContext);

    //Switches S1 S2
    __enable_interrupt();

    Buttons_init(BUTTON_S1 );
    Buttons_interruptEnable(BUTTON_S1 );

    Buttons_init(BUTTON_S2 );
    Buttons_interruptEnable(BUTTON_S2 );

    //ADC pin 6.6
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
    ADC12CTL0 |= ADC12SC + ADC12ENC;
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
        		print_string(0,24,"3.Fourier Threshold");
        		print_string(0,32,"4.Back");
        		switch(option){
        		case 1:
        			highlight_and_print_string(0,16,"2.Peak");
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

