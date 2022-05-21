 #include <msp430.h>

#define LED1 BIT0
#define LED2 BIT1
#define LED3 BIT2
#define S1 BIT5

void turnOFF(int bit);
void turnON(int bit);
void configWDT(void);
void configPins(void);
void updateLeds(void);
void timerSETUP(void);

volatile unsigned int directioncount = 2;                   //count for direction
volatile unsigned int ledcount = 0;                         //LED Counter
volatile unsigned int timercount = 0;                       //Timer Counter


/***************************************************************/
int main(void)
{
    configWDT();
    timerSETUP();
    configPins();


    turnON(LED1+LED2+LED3);                                 //Turns all LED on
    turnOFF(LED1+LED2+LED3);                                //Turns all LED off
    LPM1;
}
/**************************************************************************/
void timerSETUP(void)
    {
        BCSCTL1 = CALBC1_1MHZ;                              //1MHz
        DCOCTL = CAL_DCO_1MHZ;                              //1MHz
        TACCTL0 |= CCIE;                                    //Enable interrupt for CCR0.
        TACTL = TASSEL_2 + ID_0 + MC_1;                     //SMCLK, freq divider:1 , Up Mode
        _enable_interrupt();                                //Start interrupts
        TACCR0 = 50000;                                     //Count to 50000, approx 50ms
    }
/**************************************************************************/
void configWDT(void)
    {
        WDTCTL = WDTPW | WDTHOLD;                           // Stop watchdog timer
    }
/************************************************************************/
void configPins(void)
    {
                P1DIR |= BIT0;                              // Set P1.0 to output direction
                P1DIR |= BIT1;                              // Set P1.1 to output direction
                P1DIR |= BIT2;                              // Set P1.2 to output direction
                P1IES |= BIT5;                              // P1.5 High/Low Edge
                P1IFG &= ~BIT5;                             // P1.5 IFG Cleared
                P1IE |= BIT5;                               // P1.5 Interrupt Enabled
    }
/********************************************************************/
void updateLeds(void)
    {
        switch(ledcount%8)
            {
                case 0:
                    P1OUT = 0x00;                           //0000 0000
                    break;
                case 1:
                    P1OUT = 0x01;                           //0000 0001
                    break;
                case 2:
                    P1OUT = 0x02;                           //0000 0010
                    break;
                case 3:
                    P1OUT = 0x03;                           //0000 0011
                    break;
                case 4:
                    P1OUT = 0x04;                           //0000 0100
                    break;
                case 5:
                    P1OUT = 0x05;                           //0000 0101
                    break;
                case 6:
                    P1OUT = 0x06;                           //0000 0110
                    break;
                case 7:
                    P1OUT = 0x07;                           //0000 0111
                    break;
            }
    }
/***************************************************************/
void turnOFF(int bit)
{
    P1OUT &= ~bit;                                          //turn off all bits
}
void turnON(int bit)
{
    P1OUT |= bit;                                           //turn on all bits
}
/***************************************************************/
//Timer
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timerexample(void)
{
    timercount++;
    if(timercount%40==0)                                    // 40x50ms=2second my school number ends with 2
    {
    if(!(directioncount%2))                                 //indicate the direction of counter
        ledcount++;                                         //up if directioncount even
    else
        ledcount--;                                         //down if directioncount odd
    }
    updateLeds();                                           //updating leds

}

/***************************************************************/
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR (void)                           // Interrupt of pragma vector
        {
         directioncount++;                                  //direction up if even, down if odd
         __delay_cycles(50000);                             //for button bouncing
         P1IFG &= ~BIT5;                                    // P1.5 IFG Cleared again
         }
