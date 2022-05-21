#include <msp430.h>

/*
    Using ADC peripheral to Read data from P1.3 
*/

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                                   // Stop WDT
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
    ADC10CTL1 = INCH_3;                                         // input A3
    ADC10AE0 |= 0x08;                                           // PA.3 ADC option select

    __bis_SR_register(GIE);                                     //Enable Interrupts
    P1DIR |= 0x40;                                              // Set P1.6 output direction
    P1SEL |= 0X40;

    DCOCTL = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;

    TA0CTL = TASSEL_2 + MC_1 + TAIE;
    TA0CCR0 = 1024;
    TA0CCR1 = 1;
    TACCTL1 = OUTMOD_7;

    while(1);
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void timer(void)
{
    ADC10CTL0 |= ENC + ADC10SC;                             // Sampling and conversion start
    TA0CCR1 = ADC10MEM;
}
