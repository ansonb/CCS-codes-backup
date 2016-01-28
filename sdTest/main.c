#include <ECW.h>
#include "SDCard.h"
#include "string.h"
/*
 * main.c
 */

FRESULT rc;
// File system object
FATFS fatfs;
// File object
FIL fil;
UINT br, bw;

void appendedWrite(const char *filename, char *text, int size){
    //Open file
    rc = f_open(&fil, filename, FA_WRITE|FA_OPEN_ALWAYS);

    //Move read/write pointer to end of file for appending
    rc = f_lseek(&fil, f_size(&fil));

    if (rc)
    {
        die(rc);
    }

    // Write to file
    rc = f_write(&fil, text, size, &bw);
    if (rc)
    {
        die(rc);
    }

    // Close the file
    rc = f_close(&fil);
    if (rc)
    {
        die(rc);
    }
}


void read(const char *filename, char *rBuffer, int fSize){
    // Open file
    rc = f_open(&fil, filename, FA_READ);

    if (rc)
    {
        die(rc);
    }

    //Read from file
    rc = f_read(&fil, rBuffer, fSize, &br);
    if (rc)
    {
        die(rc);
    }

    // Close the file
    rc = f_close(&fil);
    if (rc)
    {
        die(rc);
    }
}
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    lcd_init();

    f_mount(0, &fatfs);

    appendedWrite("Xyz.txt", " Hello", strlen(" Hello"));
    appendedWrite("Xyz.txt", " Hello", strlen(" Hello"));

    //Compute size of file
    rc = f_open(&fil, "Xyz.txt", FA_READ);
    int fSize = f_size(&fil);
    rc = f_close(&fil);
    if (rc)
    {
        die(rc);
    }

    //read from file
    char *rBuffer = (char *)malloc(fSize*sizeof(char));
    read("Xyz.txt", rBuffer, fSize);

    print_int(0, 0, br);
    print_int(51, 0, fSize);
    print_string(0, 30, rBuffer);

    //WriteFile("Xyz.txt", "Hello from MSP430F5529", 22);

    unsigned char i;


     P3SEL = BIT3+BIT4;                        // P3.4,5 = USCI_A0 TXD/RXD
    //.......................
    //  P5SEL |= BIT4+BIT5;                       // Select XT1
    //
    //  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
    //  UCSCTL6 |= XCAP_3;                        // Internal load cap
    //  UCSCTL3 = 0;                              // FLL Reference Clock = XT1
    //
    //  // Loop until XT1,XT2 & DCO stabilizes - In this case loop until XT1 and DCo settle
    //  do
    //  {
    //    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
    //                                            // Clear XT2,XT1,DCO fault flags
    //    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
    //  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
    //
    //  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive strength
    //
    //  UCSCTL4 |= SELA_0 + SELS_4 + SELM_4;      // ACLK = LFTX1
    //                                            // SMCLK = default DCO
    //                                            // MCLK = default DCO
    //
      //................
      UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
      UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
      UCA0BR0 = 0x03;                           // 32kHz/9600=3.41 (see User's Guide)
      UCA0BR1 = 0x00;                           //
      UCA0MCTL = UCBRS_3+UCBRF_0;               // Modulation UCBRSx=3, UCBRFx=0
      UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
      UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

      __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, interrupts enabled
      __no_operation();                         // For debugger

    return 0;
}

// Echo back RXed character, confirm TX buffer is ready first
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(UCA0IV,4))
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:                                   // Vector 2 - RXIFG
    while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    UCA0TXBUF = UCA0RXBUF;                  // TX -> RXed character
    break;
  case 4:break;                             // Vector 4 - TXIFG
  default: break;
  }
}

