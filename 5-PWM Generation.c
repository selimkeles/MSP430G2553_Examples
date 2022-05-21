#include <msp430g2553.h>
//----------------------------------------------------------------------------------------------------------------------------------------------------
#define GREENLED BIT6
//----------------------------------------------------------------------------------------------------------------------------------------------------
void configWDT(void);
void configClock(void);
void configTimer(void);
void configPins(void);
void toggleLeds(void);
//----------------------------------------------------------------------------------------------------------------------------------------------------
void main(void){
    configWDT();
    configClock();
    configPins();
    configTimer();
    LPM0;                                                           //Low Power Mode 0 selected
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void configWDT(void) {WDTCTL = WDTHOLD + WDTPW; }
//----------------------------------------------------------------------------------------------------------------------------------------------------
void configClock(void) {
   DCOCTL = CALDCO_1MHZ;                                            // DCO set to 1Mhz
   BCSCTL1 = CALBC1_1MHZ;
   BCSCTL2 |= DIVS_3;                                               // DCO frequency divided to 8 -> 10e6/8= 125kHz
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void configPins(void){
    P1DIR |= GREENLED;                                              // Green LED out direction
    P1SEL |= GREENLED;                                              // PWM Mode selected
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void configTimer(void){
    TA0CTL =TASSEL_2 + MC_1 + ID_3;                                 // SMCLK, Up mode , SMCLKfreq/8=15.625kHz , Timer A interrupt enabled
    TA0CCR0 = 31250;                                                // Timer period = 64us -> 64us*31250=2second
//    TA0CCR1 =   7812;                                               // %25 duty cycle setted
    TA0CCR1 =   15625;                                              // %50 duty cycle setted
//    TA0CCR1 =   23437;                                              // %75 duty cycle setted
    TA0CCTL1 |= OUTMOD_7;                                           // Outpud Mod graph can be reached at datasheet
}


/*
#include <msp430g2553.h>
//----------------------------------------------------------------------------------------------------------------------------------------------------
#define GREENLED BIT6
//----------------------------------------------------------------------------------------------------------------------------------------------------
unsigned int dutyArray[5] = {6250, 12500, 18750, 25000, 31250};     // PWM array max= 31250/31250=1 full width others are %80 %60 %40 %20 respectively
unsigned volatile int idx = 0;                                      // array indexer
unsigned volatile int count = 0;                                    // timer counter for pwm duty cycle change
unsigned volatile int maxcount = 5;                                 // since pwm period is 2 -> 2*5=10   duty cycle changes with every 10 second
//----------------------------------------------------------------------------------------------------------------------------------------------------
void configWDT(void);
void configClock(void);
void configTimer(void);
void configPins(void);
void toggleLeds(void);
//----------------------------------------------------------------------------------------------------------------------------------------------------
void main(void){
    configWDT();
    configClock();
    configPins();
    configTimer();
    __bis_SR_register(LPM0_bits + GIE);                             // Low Power Mode selected. Interrupts enabled
    __no_operation();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void configWDT(void) {WDTCTL = WDTHOLD + WDTPW; }
//----------------------------------------------------------------------------------------------------------------------------------------------------
void configClock(void) {
   DCOCTL = CALDCO_1MHZ;                                            // DCO set to 1Mhz
   BCSCTL1 = CALBC1_1MHZ;
   BCSCTL2 |= DIVS_3;                                               // DCO frequency divided to 8 -> 10e6/8= 125kHz
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void configPins(void){
    P1DIR |= GREENLED;                                              // Green LED out direction
    P1SEL |= GREENLED;                                              // PWM Mode selected
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void configTimer(void){
    TA0CTL =TASSEL_2 + MC_1 + ID_3 + TAIE;                          // SMCLK, Up mode , SMCLKfreq/8=15.625kHz , Timer A interrupt enabled
    TA0CCR0 = 31250;                                                // Timer period = 64us -> 64us*31250=2second
    TA0CCR1 = dutyArray[idx];                                       // %20 duty cycle setted
    TA0CCTL1 |= OUTMOD_7;                                           // Outpud Mod graph can be reached at datasheet
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
#pragma vector = TIMER0_A1_VECTOR
__interrupt void timer(void) {
    TA0CTL &=  ~TAIFG;                                              // Timer A interrupt flag cleared manually since it is multitasking interrrupt vector
    if (++count % maxcount == 0) {                                  // maxcount=5 5*2=10sec then every 10 sec enter the if statement
        ++idx;                                                      // increase index to switch next duty cycle
        idx %= maxcount;                                            // mod5 of index since it increases to larger values and array only has 5 element
        TA0CCR1 = dutyArray[idx];                                   // Duty cycle increased
    }
}
*/
