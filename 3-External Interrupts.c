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

volatile unsigned int count = 0;                                //Push Counter

/******************************************************************************/
int main(void)
    {
            configWDT();                                //Stops WDt
            configPins();                               //Init function
            turnON(LED1+LED2+LED3);                     //Turns all LED on
            turnOFF(LED1+LED2+LED3);                    //Turns all LED off
            _bis_SR_register(LPM4_bits + GIE);          // Enter LPM4 w/ interrupt
            _no_operation();                            // For debugger
    }
/**************************************************************************/
void configWDT(void)
    {
        WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer
    }
/************************************************************************/
void configPins(void)
    {
                P1DIR |= BIT0;              // Set P1.0 to output direction
                P1DIR |= BIT1;              // Set P1.1 to output direction
                P1DIR |= BIT2;              // Set P1.2 to output direction
                P1IES |= BIT5;              // P1.5 High/Low Edge
                P1IFG &= ~BIT5;             // P1.5 IFG Cleared
                P1IE |= BIT5;               // P1.5 Interrupt Enabled
    }
/********************************************************************/
void updateLeds(void)
    {
        switch(count%8)
            {
                case 0:
                    P1OUT = 0x00;                   //0000 0000
                    break;
                case 1:
                    P1OUT = 0x01;                   //0000 0001
                    break;
                case 2:
                    P1OUT = 0x02;                   //0000 0010
                    break;
                case 3:
                    P1OUT = 0x03;                   //0000 0011
                    break;
                case 4:
                    P1OUT = 0x04;                   //0000 0100
                    break;
                case 5:
                    P1OUT = 0x05;                   //0000 0101
                    break;
                case 6:
                    P1OUT = 0x06;                   //0000 0110
                    break;
                case 7:
                    P1OUT = 0x07;                   //0000 0111
                    break;
            }
    }
/***************************************************************/
void turnOFF(int bit)
{
    P1OUT &= ~bit;                                  //turn off all bits
}
void turnON(int bit)
{
    P1OUT |= bit;                                   //turn on all bits
}
/***************************************************************/
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR (void)   // Interrupt of pragma vector
        {
         count++;                   //led number
         updateLeds();              //updating leds
         __delay_cycles(250000);     //for button bouncing
         P1IFG &= ~BIT5;            // P1.5 IFG Cleared again
         }
