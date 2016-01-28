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


#include <stdint.h>
#include "driverlib.h"
#include "grlib.h"
#include "LcdDriver/Dogs102x64_UC1701.h"
#include "Images/images.h"


uint16_t timeoutCounter;
tContext g_sContext;
tRectangle g_sRect;

int32_t stringWidth = 0;
void Board_init(void);
void Clock_init(void);
void Delay(void);


void main(void)
{
	tRectangle myRectangle1 = { 5, 10, 60, 50};
	tRectangle myRectangle2 = { 30, 20, 100, 60};
	tRectangle myRectangle3 = { 0, 0, 101, 63};

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

    // Intro Screen
    GrStringDrawCentered(&g_sContext,
    		"How to use MSP430",
    		AUTO_STRING_LENGTH,
    		51,
    		16,
    		TRANSPARENT_TEXT);
    GrStringDrawCentered(&g_sContext,
    		"Graphics Library",
    		AUTO_STRING_LENGTH,
    		51,
    		32,
    		TRANSPARENT_TEXT);
    GrStringDrawCentered(&g_sContext,
    		"Primitives",
    		AUTO_STRING_LENGTH,
    		51,
    		48,
    		TRANSPARENT_TEXT);
    Delay();
    GrClearDisplay(&g_sContext);


    // Draw pixels and lines on the display
    GrStringDraw(&g_sContext,
    		"Draw Pixels",
    		AUTO_STRING_LENGTH,
    		20,
    		0,
    		TRANSPARENT_TEXT);
    GrStringDraw(&g_sContext,
    		"& Lines",
    		AUTO_STRING_LENGTH,
    		30,
    		10,
    		TRANSPARENT_TEXT);
    GrPixelDraw(&g_sContext, 10, 10);
    GrPixelDraw(&g_sContext, 10, 12);
    GrPixelDraw(&g_sContext, 12, 12);
    GrPixelDraw(&g_sContext, 12, 10);
    GrLineDraw(&g_sContext, 15, 15, 60, 60);
    GrLineDraw(&g_sContext, 10, 50, 90, 10);
    GrLineDraw(&g_sContext,
    		0,
    		GrContextDpyHeightGet(&g_sContext) - 1,
    		GrContextDpyWidthGet(&g_sContext) - 1,
    		GrContextDpyHeightGet(&g_sContext) - 1);
    Delay();
    GrClearDisplay(&g_sContext);

    // Draw circles on the display
    GrStringDrawCentered(&g_sContext,
    		"Draw Circles",
    		AUTO_STRING_LENGTH,
    		51,
    		5,
    		TRANSPARENT_TEXT);
    GrCircleDraw(&g_sContext, 30, 50, 10);
    GrCircleFill(&g_sContext, 65, 37, 23);
    Delay();



    GrClearDisplay(&g_sContext);

    // Draw rectangles on the display
    GrStringDrawCentered(&g_sContext,
    		"Draw Rectangles",
    		AUTO_STRING_LENGTH,
    		51,
    		5,
    		TRANSPARENT_TEXT);
    GrRectDraw(&g_sContext, &myRectangle1);
    GrRectFill(&g_sContext, &myRectangle2);
    // Text won't be visible on screen due to transparency
    GrStringDrawCentered(&g_sContext,
    		"Normal Text",
    		AUTO_STRING_LENGTH,
    		65,
    		30,
    		TRANSPARENT_TEXT);
    // Text draws foreground and background for opacity
    GrStringDrawCentered(&g_sContext,
    		"Opaque Text",
    		AUTO_STRING_LENGTH,
    		65,
    		40,
    		OPAQUE_TEXT);
    GrContextForegroundSet(&g_sContext, ClrWhite);
    GrContextBackgroundSet(&g_sContext, ClrBlack);
    // Text draws with inverted color to become visible
    GrStringDrawCentered(&g_sContext,
    		"Invert Text",
    		AUTO_STRING_LENGTH,
    		65,
    		50,
    		TRANSPARENT_TEXT);
    Delay();
    GrClearDisplay(&g_sContext);

    // Invert the foreground and background colors
    GrContextForegroundSet(&g_sContext, ClrBlack);
    GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangle3);
    GrContextForegroundSet(&g_sContext, ClrWhite);
    GrContextBackgroundSet(&g_sContext, ClrBlack);
	GrStringDrawCentered(&g_sContext,
			"Invert Colors",
			AUTO_STRING_LENGTH,
			51,
			5,
			TRANSPARENT_TEXT);
	GrRectDraw(&g_sContext, &myRectangle1);
	GrRectFill(&g_sContext, &myRectangle2);
	// Text won't be visible on screen due to transparency
    GrStringDrawCentered(&g_sContext,
    		"Normal Text",
    		AUTO_STRING_LENGTH,
    		65,
    		30,
    		TRANSPARENT_TEXT);
    // Text draws foreground and background for opacity
    GrStringDrawCentered(&g_sContext,
    		"Opaque Text",
    		AUTO_STRING_LENGTH,
    		65,
    		40,
    		OPAQUE_TEXT);
    GrContextForegroundSet(&g_sContext, ClrBlack);
    GrContextBackgroundSet(&g_sContext, ClrWhite);
    // Text draws with inverted color to become visible
    GrStringDrawCentered(&g_sContext,
    		"Invert Text",
    		AUTO_STRING_LENGTH,
    		65,
    		50,
    		TRANSPARENT_TEXT);
	Delay();
    GrContextForegroundSet(&g_sContext, ClrBlack);
    GrContextBackgroundSet(&g_sContext, ClrWhite);
	GrClearDisplay(&g_sContext);

    // Draw Images on the display
    GrImageDraw(&g_sContext, &LPRocket_96x37_1BPP_UNCOMP, 3, 13);
    Delay();
    GrClearDisplay(&g_sContext);
    GrImageDraw(&g_sContext, &TI_Logo_69x64_1BPP_UNCOMP, 16, 0);

    while(1)
    {
    }

}

void Board_init(void)
{
    // Setup XT1 and XT2
  GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P5,
        GPIO_PIN2 + GPIO_PIN3 + 
        GPIO_PIN4 + GPIO_PIN5
          );

   GPIO_setOutputLowOnPin(
        GPIO_PORT_P1,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2 + 
        GPIO_PIN3 + GPIO_PIN4 + GPIO_PIN5
        );
   
    // Configure LED ports
    GPIO_setAsOutputPin(
        GPIO_PORT_P1,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2 + 
        GPIO_PIN3 + GPIO_PIN4 + GPIO_PIN5
        );
    
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P8,
        GPIO_PIN1 + GPIO_PIN2
        );
    
    GPIO_setAsOutputPin(
        GPIO_PORT_P8,
        GPIO_PIN1 + GPIO_PIN2
        );
    
    // Configure button ports
    // Buttons on P1.7/P2.2 are inputs
    GPIO_setAsInputPin(
        GPIO_PORT_PA,
        GPIO_PIN7 + GPIO_PIN10
        );

    // Configure CapTouch ports
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P1,
        GPIO_PIN1 + GPIO_PIN2 + GPIO_PIN3 + 
        GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6
        );
    GPIO_setAsOutputPin(
        GPIO_PORT_P1,
        GPIO_PIN1 + GPIO_PIN2 + GPIO_PIN3 + 
        GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6
        );
    
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P6,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2 + GPIO_PIN3 + 
        GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7
        );
    GPIO_setAsInputPin(
        GPIO_PORT_P6,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2 + GPIO_PIN3 + 
        GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7
        );

    // Configure Cma3000 ports
    // ACCEL_INT pin is input
    GPIO_setAsInputPin(
        GPIO_PORT_P2,
        GPIO_PIN5
        );
    
    // SCK
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P2,
        GPIO_PIN7
        );
    GPIO_setAsOutputPin(
        GPIO_PORT_P2,
        GPIO_PIN7
        );
    
    // ACCEL_SIMO, ACCEL_CS, ACCEL_PWR to low
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P3,
        GPIO_PIN3 + GPIO_PIN5 + GPIO_PIN6
        );
    
    // ACCEL_SOMI pin is input
    GPIO_setAsInputPin(
        GPIO_PORT_P3,
        GPIO_PIN4
        );
    
    // ACCEL_SIMO, ACCEL_CS, ACCEL_PWR as outp
    GPIO_setAsOutputPin(
        GPIO_PORT_P3,
        GPIO_PIN3 + GPIO_PIN5 + GPIO_PIN6
        );

    // Configure Dogs102x6 ports
    // LCD_C/D, LCD_RST
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P5,
        GPIO_PIN6 + GPIO_PIN7
        );

    GPIO_setAsOutputPin(
        GPIO_PORT_P5,
        GPIO_PIN6 + GPIO_PIN7
        );
    
    // LCD_CS, LCD_BL_EN
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P7,
        GPIO_PIN4 + GPIO_PIN6
        );
   
    GPIO_setAsOutputPin(
        GPIO_PORT_P7,
        GPIO_PIN4 + GPIO_PIN6
        );
    
    // SIMO, SCK
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P4,
        GPIO_PIN1 + GPIO_PIN3
        );
    
    // SOMI pin is input
    GPIO_setAsInputPin(
        GPIO_PORT_P4,
        GPIO_PIN2
        );
    
    GPIO_setAsOutputPin(
        GPIO_PORT_P4,
        GPIO_PIN1 + GPIO_PIN3 
        );


    // Configure SDCard ports
    // SD_CS to high
    GPIO_setOutputHighOnPin(
        GPIO_PORT_P3,
        GPIO_PIN7
        );
    GPIO_setAsOutputPin(
        GPIO_PORT_P3,
        GPIO_PIN7
        );

    // Configure Wheel ports
    // A5 ADC input
    GPIO_setAsInputPin(
        GPIO_PORT_P6,
        GPIO_PIN5
        );
    
    // POT_PWR
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P8,
        GPIO_PIN0
        );
    GPIO_setAsOutputPin(
        GPIO_PORT_P8,
        GPIO_PIN0
        );

    // Configure unused ports for low power
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P2,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN3 + 
        GPIO_PIN4 + GPIO_PIN6
        );
    GPIO_setAsOutputPin(
        GPIO_PORT_P2,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN3 + 
        GPIO_PIN4 + GPIO_PIN6
        );

    GPIO_setOutputLowOnPin(
        GPIO_PORT_P3,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2
        );
    GPIO_setAsOutputPin(
        GPIO_PORT_P3,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2
        );

    GPIO_setOutputLowOnPin(
        GPIO_PORT_P4,
        GPIO_PIN0 + GPIO_PIN6 + GPIO_PIN7
        );
    GPIO_setAsOutputPin(
        GPIO_PORT_P4,
        GPIO_PIN0 + GPIO_PIN6 + GPIO_PIN7
        );
    

    GPIO_setOutputLowOnPin(
        GPIO_PORT_P5,
        GPIO_PIN1
        );
    GPIO_setAsOutputPin(
        GPIO_PORT_P5,
        GPIO_PIN1
        );

    GPIO_setOutputLowOnPin(
        GPIO_PORT_P6,
        GPIO_PIN6 + GPIO_PIN7
        );
    GPIO_setAsOutputPin(
        GPIO_PORT_P6,
        GPIO_PIN6 + GPIO_PIN7
        );

   GPIO_setOutputLowOnPin(
        GPIO_PORT_P7,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2 + 
        GPIO_PIN3 + GPIO_PIN5+ GPIO_PIN7
        );
    GPIO_setAsOutputPin(
        GPIO_PORT_P7,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2 + 
        GPIO_PIN3 + GPIO_PIN5+ GPIO_PIN7
        );
}

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
	__delay_cycles(SYSTEM_CLOCK_SPEED * 4);
}




