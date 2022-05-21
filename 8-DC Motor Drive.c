#include <msp430.h>

int directioncount = 2;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                                   // Stop WDT
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
    ADC10CTL1 = INCH_0;                                         // input A3
    ADC10AE0 |= 0x01;                                           // PA.3 ADC option select

    __bis_SR_register(GIE);                                     //Enable Interrupts
    P1DIR |= BIT4 + BIT5 + BIT6;                                              // Set P1.6 output direction
    P1SEL |= BIT6;

    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    TA0CTL = TASSEL_2 + MC_1 + TAIE;
    TA0CCR0 = 1024;
    TA0CCR1 = 1;
    TACCTL1 = OUTMOD_7;

    P1IES |= BIT3;                                              // P1.5 High/Low Edge
    P1IFG &= ~BIT3;                                             // P1.5 IFG Cleared
    P1IE |= BIT3;                                               // P1.5 Interrupt Enabled

}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void timer(void)
{
    ADC10CTL0 |= ENC + ADC10SC;                                 // Sampling and conversion start
    TA0CCR1 = ADC10MEM;
    TACTL &= ~TAIFG;

}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR (void)                               // Interrupt of pragma vector
        {
         directioncount++;                                      // direction up if even, down if odd
         __delay_cycles(50000);                                // for button bouncing
         if(directioncount%2){
             P1OUT |= BIT4;
             P1OUT &= ~BIT5;
         }
         else{
             P1OUT |= BIT5;
             P1OUT &= ~BIT4;
         }
         P1IFG &= ~BIT3;                                        // P1.5 IFG Cleared again
         }
