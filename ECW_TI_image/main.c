#include"lib.c"

uint16_t timeoutCounter;
tContext g_sContext;

//UI variables
int menu=0,option=0,exec_counter=0,eye_enable=0;
int max_menu=5;
int total_options[]={4,4,5,6,2};
int disp_counter=1;

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



void main(void)
{
    set_up();

    buttonsPressed = 0;
    while(1){

    	exec_counter=0;
    	//to select menu

	    //store only when any value has changed
		if(calibrated_adc==1||calibrated_F==1||calibrated_steady==1){
             char storage[]={AdcThreshold, dcval, steady_crest, fourier_offset, FThreshold};
				 eeprom_write_bytes(storage,5);//check for FThreshold>255

	 /*   for(i=0;i<4;i++){
			P1OUT = 0b00000001;
	        _delay_ms(250);
	        P1OUT = 0b00000000;
	        _delay_ms(250);
	    }
*/
			 }


		tempF=255;
		temp=0;
		//to refresh the  thresholds only when switches are pressed
		calibrated_adc=0;
        calibrated_F=0;
		calibrated_steady=0;

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


				tempF=255;
				temp=0;
				//to refresh the  thresholds only when switches are pressed
				calibrated_adc=0;
                calibrated_F=0;
				calibrated_steady=0;

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
        								         print_string(0,0,"Blink to calib");
        								         print_int(50, 30, AdcThreshold);
        								         print_string(0,56,"*S2=ESC*");
                                                 _delay_ms(200);
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
        								 print_string(0,0,"Blink to calib");
        								 print_int(50, 30, AdcThreshold);
        								 print_string(0,56,"*S2=ESC*");

        								 _delay_ms(200);
        									 }

        								 if(AdcThreshold==255) AdcThreshold=steady_crest;//if 50 hz noise
        								 lcd_clear();

        								 buttonsPressed=0;
        								 disp_counter=1;

        			}
        			break;

        		case 2:
        			highlight_and_print_string(0,24,"3.Fourier");
        			if(exec_counter==1){
        				exec_counter=0;

       				 //calibrate FThreshold
       				 while(!(buttonsPressed & BUTTON_S2)){
       				 if(calibrated_F==0){
       					//write anything that you want to execute only once in the loop
       					 lcd_clear();

       				 }
       				 X=dft();
       				 if(X>fourier_offset+10 && tempF>X){  //+10 is for lesser sensitivity. If offset is more use % of fourier_offset
       					 FThreshold=X;
       					 tempF=X;
       				 }
       				 calibrated_F=1;
       				 lcd_clear();
   					 print_string(0,0,"Blink to calibrate");
   					 print_string(0,56,"*S2=ESC*");
       				 print_int(50,30,(int)X);
       				 _delay_ms(200);
       				 }
       				    lcd_clear();
        				buttonsPressed=0;
        				disp_counter=1;
        			}
        			break;

        		case 3:
        			highlight_and_print_string(0,32,"4.Back");
        			if(exec_counter==1){
        				exec_counter=0;
        				menu=0;
        				option=0;
        				disp_counter=1;
        			}
        			break;

        		default:
        			highlight_and_print_string(0,8,"1.Steady Values");
        			option=0;
        			if(exec_counter==1){
        				exec_counter=0;
   				     //initialize before setting
   					 dcval=0;
   					 fourier_offset=0;
   					 steady_trough=255,steady_crest=0;

   					 lcd_clear();
   					 print_string(0,0,"Focus on the dot");
   					 print_string(32,16,"for 3s ");
   					 print_string(40,30,"(.)");
   					 _delay_s(3);

   					 //compute fourier_offset
   					 for(i=0;i<10;i++){  //will check for 10*100 ms
   					  check_fourier_offset();
   					 }
   					 //compute dc_val
   					 for(i=0;i<2000;i++){ //average 2000 samples collected over 2 sec
   					 input=adc_read();
   					  dcval+=(float)input/2000;
   					  if(steady_crest<input) steady_crest=input;
   					  if(steady_trough>input) steady_trough=input;
   					  _delay_ms(1);
   					 }
   					 steady_crest=steady_crest+(steady_crest-dcval)*0;  //0% more than the steady peak
   					 steady_trough=steady_trough-(dcval-steady_trough)*0;

   					 lcd_clear();
   					 print_string(0,0,"Done Calibrating!");
   					 print_string(0,16,"Fourier Off:");
   					 print_int(80,16,fourier_offset);
   					 print_string(0,32,"DC:");
   					 print_int(80,32,dcval);
   					 print_string(0,40,"Steady Crest:");
   					 print_int(80,40,steady_crest);
   					 print_string(0,56,"*S2=ESC*");
   					 _delay_s(3);
   					 while(!(buttonsPressed & BUTTON_S2));
   					 lcd_clear();

   					 calibrated_steady=1;

   					 //to display when it goes back
					 buttonsPressed=0;
					 disp_counter=1;
        			}
        			break;
        		}
        		break;

        	case 2:
        		print_string(0,0,"===Thresholds===");
        		print_string(0,8,"1.DC.........");
        		print_int(80,8,dcval);
        		print_string(0,16,"2.Steady Pk..");
        		print_int(80,16,steady_crest);
        		print_string(0,24,"3.Peak.......");
        		print_int(80,24,AdcThreshold);
        		print_string(0,32,"4.Fourier....");
        		print_int(80,32,FThreshold);
        		print_string(0,56,"*S2=ESC*");
        		while(!(buttonsPressed & BUTTON_S2));
        		//to check slope
        		buttonsPressed=0;
                while(!(buttonsPressed & BUTTON_S2)){
                	X=dft();
                	print_int(48,24,max_input);
                	print_int(48,32,max_slope);
                	_delay_ms(200);
                	lcd_clear()
                }

                buttonsPressed=0;
				menu=0;
				option=0;
				disp_counter=1;
        		break;
        	case 3:
        		print_string(0,0,"===Eye Control===");
        		print_string(0,8,"1.Wait      ");
        		print_string(0,16,"2.Left   ");
        		print_string(0,24,"3.Right   ");
        		print_string(0,32,"4.Forward   ");
        		print_string(0,40,"5.Backward   ");
        		print_string(0,56,"*S2=ESC*");

    			eye_control();

				menu=0;
				option=0;
				disp_counter=1;
        		/*if(exec_counter==1){
        			exec_counter=0;
        			eye_control();
        		}

        		if(buttonsPressed & BUTTON_S2){
        			buttonsPressed=0;
    				menu=0;
    				option=0;
    				disp_counter=1;
        		}*/
        		/*switch(option){
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
        		}*/
        		break;

        	//debug signal on lcd
        	case 4:
        		print_string(0,0,"S1 pause/resume");
        		print_string(0,56,"S2 Back");
        		plot();
    		    menu=0;
    		    option=0;
    		    disp_counter=1;
        		break;
        	default:break;
        	}
        }
    }


}
