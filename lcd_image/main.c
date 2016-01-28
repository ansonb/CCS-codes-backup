#include <stdint.h>
#include "driverlib.h"
#include "grlib.h"
#include "LcdDriver/Dogs102x64_UC1701.h"
#include "Images/images.h"
#include "stdio.h"

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



void main(void)
{


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

    P7OUT |=0b00001111;

    GrImageDraw(&g_sContext, &perfect_wc1BPP_UNCOMP, 16, 0);
}

