#include <msp430.h> 

unsinged int HallData;
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	    // stop watchdog timer
	P1REN = 0b00111000;             // PORTS 1.3 1.4 1.5 Resistors Enabled
	P2DIR = 0b00111111;
	P2OUT = 0;

	while(1)
	{
	    HallData = P1IN;
	    HallData &= (0b00111000);
	    HallData = HallData>>3;

	    switch(HallData)
	    {
	    case 1:
	    P2OUT=0b00100100;
	    break;
        case 2:
        P2OUT=0b00010010;
        break;
        case 3:
        P2OUT=0b00000110;
        break;
        case 4:
        P2OUT=0b00001001;
        break;
        case 5:
        P2OUT=0b00100001;
        break;
        case 6:
        P2OUT=0b00011000;
        break;
        default:
        P2OUT=0;
	    }
	}
	return 0;
}
