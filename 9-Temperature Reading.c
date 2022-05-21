#include <msp430.h>
/*************************************************************/
/******************PRE DEFINED VALUES*************************/
/*************************************************************/

unsigned char number[10] = {0b00000000, 0b00000001, 0b000000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00001000, 0b00001001};
volatile unsigned int timercount = 0;                           //Timer Counter
unsigned PullUpV,digit1,digit2,digit3,temperature;
const unsigned int K=4100;
const float T0 = 1/298.15;
/*************************************************************/
/******************FUNCTION PROTOS****************************/
/*************************************************************/
void wdt(void);
void adcsetup(void);
void timersetup(void);
void init(void);
 unsigned int adcread(void);
void update7segment(unsigned int S);
float logN(int num,float base);
/*************************************************************/
/***********************MAIN**********************************/
/*************************************************************/
void main(void)
{
  init();
  while(1);
}
/*************************************************************/
/**********************FUNCTIONS******************************/
/*************************************************************/
void wdt(void)
{
  WDTCTL = WDTPW + WDTHOLD;                                     // Stop WDT
}
/*************************************************************/
void adcsetup(void)
{
  ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
  ADC10CTL1 = INCH_4;                                           // input A4
  ADC10AE0 |= BIT4;                                             // PA.4 ADC option select
}
/*************************************************************/
void timersetup(void)
{
  DCOCTL = CALDCO_1MHZ;
  BCSCTL1 = CALBC1_1MHZ;
  TACCTL0 |= CCIE;                                              //Enable interrupt for CCR0.
  TACTL = TASSEL_2 + ID_0 + MC_1;                               //SMCLK, freq divider:1 , Up Mode
  TA0CCR0 = 50000;
}
/*************************************************************/
void init(void)
{
  wdt();
  P1DIR |= BIT0 + BIT1 + BIT2 + BIT3;                           // Set P1.0 P1.1 P1.2 P1.3 output direction
  P2DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4;                    // Set P2.0 P2.1 P2.2 P2.3 P2.4 output direction
  adcsetup();
  timersetup();
  __bis_SR_register(GIE);                                       //Enable Interrupts
}
/*************************************************************/
 unsigned int adcread(void)
{
  ADC10CTL0 |= ENC + ADC10SC;                                   // Sampling and conversion start
  return(ADC10MEM);
}
/*************************************************************/
void update7segment(unsigned int S)
{
    float result;

    result = 1024 - S;
    result = result / S;
    result = logN(result,2.71);
    result = result / K;
    result = result + (T0);
    result = 1 / result;
    result = result - 273.15;
    temperature = result;

    digit1 = temperature%10;
    temperature = temperature/10;
    digit2 = temperature%10;
    temperature = temperature/10;
    digit3 = temperature%10;
    temperature = temperature/10;

    P1OUT = number[digit1];
    P2OUT = number[digit2];
     if (digit3)
     {
        P2OUT |= BIT4;
     }
     else
     {
        P2OUT &= ~BIT4;
     }
}
/*************************************************************/
float logN(int num,float base)
{
      if(num<base)
           return 0;
     return 1 + logN(num/base,base);
}
/*************************************************************/
/*****************INTERRUPT***********************************/
/*************************************************************/
#pragma vector = TIMER0_A1_VECTOR
__interrupt void timer(void)
{
  timercount++;
  if(timercount%20==0)                                          // 20x50ms =1 second
  {
    update7segment(adcread());
  }
}
