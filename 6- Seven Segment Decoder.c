/*
 * This experiment sets Msp430 as 7 segment decoder for given 2 bit 2 inputs
 *
 * In addition to these two inputs, one bit chooses operation types which are addition and subtraction
 *
 *
 * */

#include <msp430.h> 


unsigned int input;                         // raw input data
int a,b,c;                                  // inputs for operations (a: Input 1 , b: Input 2 , c: operation type)
unsigned int mask=0x03;                     // since operations are 2 bits, 2 bit mask for reading stuff

unsigned char array[7] = {0b00000000, 0b00000001, 0b000000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110};         // All seven numbers for display purposes on 7 Segment (3+3=6 max)

void init(void);                            // initialize function


void main(void)
{

    init();

	while(1)
	{

	    input = P2IN;                       // gets raw data
	    a = input & mask;                   // takes last 2 bit as a from P2.0 and P2.1
	    input = input>>2;                   // shifts raw data to obtain P2.2 and P2.3 in least significant 2 bit
	    b = input & mask;                   // takes P2.2 and P2.3 data to b
	    input = input>>2;                   // shifts P2.4 data to lsb
	    c = input & BIT0;                   // takes lsb data which is P2.4 to c

	    if(c)
	    {                                   // c=1 means addition

	        P1OUT = array[a+b];             //print result to 7 segment display
	        P2OUT &= ~BIT5;                 // LED is off since no negative number might occur at this operation

	    }
	    else                                // subtraction
	    {

	        if((a-b)>=0)                    // if subtraction result is positive or zero
	        {

	            P1OUT = array[a-b];         //print result to 7 segment display
	            P2OUT &= ~BIT5;             // LED is off since no negative number might occur at this operation

	        }
	        else                            // if subtraction result is negative
	        {

                P1OUT = 0xff;               // stop displaying (even dont display zero just shut down)
                P2OUT |= BIT5;              // led which indicates negative result on


	        }


	    }

	}
	
}


void init(void)
{

    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    P1DIR = 0x0f;                           // P1.0 to P1.3 all 5 pins are selected as output for 7 segment display decoder
    P2DIR = BIT5;                           // Only P2.5 output for dot pin in 7 segment display
    P2REN = 0x1f;                           // P2.0 to P2.4 all 5 pins selected as input for addition and subtraction operations.
    P2OUT = 0x1f;                           // P2.0 to P2.4 all 5 pins configured as pull-up network

}
