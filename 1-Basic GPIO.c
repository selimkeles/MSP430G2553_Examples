#include<msp430.h>

/*
//   This code takes input from P1.2 port when we push to the button port state changes to ground and at that moment led turns of



int main (void){
        WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer
        P1DIR |= 0x40 ;                             // Set P1.6 to output direction
        P1REN |= 0x08 ;                             // Enable P1.3 Pull-Up resistor
        P1OUT |= 0X08 ;                             // Make P1.3 High(3.3V)
        while (1){
            if((P1IN & BIT3)){                      // If button is open (P1.3 HIGH)
                P1OUT = P1OUT | BIT6 ;              //... turn on LED
                }                                   // or P1OUT |= BIT0 ;
            else{
                P1OUT = P1OUT & ~BIT6;              //...else turn it off.
                                                    // or P1OUT &= ~BIT0
                }
        }
}


*/


// (2a) Reverse effect this time led blinks when we press to button

/*
int main (void){
        WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer
        P1DIR |= 0x40 ;                             // Set P1.6 to output direction
        P1REN |= 0x08 ;                             // Enable P1.3 Pull-Up resistor
        P1OUT |= 0X08 ;                             // Make P1.3 High(3.3V)
        while (1){
            if(!(P1IN & BIT3)){                      // If button is closed (P1.3 LOW)
                P1OUT = P1OUT | BIT6 ;              //... turn on LED
                }                                   // or P1OUT |= BIT0 ;
            else{
                P1OUT = P1OUT & ~BIT6;              //...else turn it off.
                                                    // or P1OUT &= ~BIT0
                }
        }
}

*/




//  (2b) delay 1 sec after push button since crystal works at 1.2Mhz base clock cyle I used __delay_cycles(1200000) function
int main (void){
        WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer
        P1DIR |= 0x40 ;                             // Set P1.6 to output direction
        P1REN |= 0x08 ;                             // Enable P1.3 Pull-Up resistor
        P1OUT |= 0X08 ;                             // Make P1.3 High(3.3V)
        while (1){
            if(!(P1IN & BIT3)){                      // If button is closed (P1.3 LOW)
                P1OUT = P1OUT | BIT6 ;              //... turn on LED
                __delay_cycles(1200000);            // 1.2 MHz equals to 1 second since clock is 1.2MHz
                P1OUT = P1OUT & ~BIT6;              // After 1 sec wait turn off the LED
                }                                   // or P1OUT |= BIT0 ;
            else{
                P1OUT = P1OUT & ~BIT6;              //...else turn it off.
                                                    // or P1OUT &= ~BIT0
                }
        }
}


/*

//  (2c) Toggle Leds

int main (void){
        WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer
        P1DIR |= 0x41 ;                             // Set P1.6 AND P1.0 to output direction
        P1REN |= 0x08 ;                             // Enable P1.3 Pull-Up resistor
        P1OUT |= 0X08 ;                             // Make P1.3 High(3.3V)
        while (1){
            if(P1IN & BIT3){                        // If button is open (P1.3 HIGH)
                if(P1IN&BIT0)                       // Clear red LED if it is active
                    P1OUT=0x08;

                P1OUT |= BIT6;                      // green LED active

            }
            else{
                if(P1IN&BIT6)                       // Clear green LED if it is active
                    P1OUT=0x08;

                P1OUT |= BIT0;                      //red LED active
            }

        }
}

*/
