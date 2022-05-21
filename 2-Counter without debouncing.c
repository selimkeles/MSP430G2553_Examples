/*
    2 Bit Binary Counter Using onboard LEDs and preventing debouncing 
*/

#include<msp430.h>


void configWDT(void);
void configPins(void);
void updateLeds(int count);

//BIT6 Green LED
//BIT0 Red LED
//BIT3 PULL UP

int main (void){
    configWDT();                                //Stops WDt
    configPins();                               //Init function
    int count=0;                                //Push Counter
    while(1)
    {
        if(!(P1IN & BIT3))                      // If button is closed (P1.3 HIGH)
            {
                count++;
                __delay_cycles(3e5);            //clock is 1.2MHz then 300kHz equals to 0.25 second delay it is enough for debouncing
                updateLeds(count);              //Blink Led function
            }



    }

}

void configWDT(void)
{
    WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer
}

void configPins(void)
{
    P1DIR |= 0x41 ;                             // Set P1.6 AND P1.0 to output direction
    P1REN |= 0x08 ;                             // Enable P1.3 Pull-Up resistor
    P1OUT |= 0x08 ;                             // Make P1.3 High(3.3V)
}

void updateLeds(int count)
{
    switch(count%4)
        {
            case 0:
                P1OUT = 0x08;                   //0000 1000
                break;
            case 1:
                P1OUT = 0x48;                   //0100 1000
                break;
            case 2:
                P1OUT = 0x09;                   //0000 1001
                break;
            case 3:
                P1OUT = 0x49;                   //0100 1001
                break;


        }
}
