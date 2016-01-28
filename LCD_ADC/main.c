/* --COPYRIGHT--,BSD
 * Copyright (c) 2013, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

#include <msp430.h>
#include <math.h>
#include <stdio.h>
#include "HAL/HAL_Dogs102x6.h"
#include "HAL/HAL_Buttons.h"
#include "HAL/HAL_Board.h"


void main(void)
{
	    // Stop WDT
	    WDTCTL = WDTPW + WDTHOLD;

	    // Set up LCD
	    Dogs102x6_init();
	    Dogs102x6_backlightInit();
	    Dogs102x6_setBacklight(11);
	    Dogs102x6_setContrast(11);
	    Dogs102x6_clearScreen();

	    __enable_interrupt();

	    Buttons_init(BUTTON_S2);
	    Buttons_interruptEnable(BUTTON_S2);
	    buttonsPressed = 0;

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
	    unsigned int sample1,sample2,i=0;
	    while(1)
	    {
	          if(i == 101)
	          {
	              Dogs102x6_clearScreen();
	              i = 0;
	           }
	           ADC12CTL0 |= ADC12SC + ADC12ENC;
	           // Start sampling/conversion
	           while (ADC12CTL1 & ADC12BUSY) __no_operation();
	           sample1 = ADC12MEM0 & 0x0FFF;
	           __delay_cycles(10000);
	           ADC12CTL0 |= ADC12SC + ADC12ENC;
	           // Start sampling/conversion
	           while (ADC12CTL1 & ADC12BUSY) __no_operation();
	           sample2 = ADC12MEM0 & 0x0FFF;
	           Dogs102x6_lineDraw(i,63-sample1/64,i+1,63-sample2/64,0);
	           if(buttonsPressed)
	           {
	               buttonsPressed = 0;
	               while(!buttonsPressed);
	               buttonsPressed = 0;
	           }
	           ++ i;
	      }

}
