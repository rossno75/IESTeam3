#include "RGBLED.h"

void RGB_Init () {
    P6DIR |= BIT0 | BIT1 | BIT2;              // P6.0, P6.1, P6.2 output
    P6SEL0 |= BIT0 | BIT1 | BIT2;             // P6.0, P6.1, P6.2 options select
    P6SEL1 &= ~(BIT0 | BIT1 | BIT2);          // P6.0, P6.1, P6.2 options select
    
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    TB3CCR0 = 1024-1;                         // PWM Period
    TB3CCTL1 = OUTMOD_3;                      // CCR1 set/reset
    TB3CCTL2 = OUTMOD_3;                      // CCR2 set/reset
    TB3CCTL3 = OUTMOD_3;                      // CCR3 set/reset
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR
}

// Description of function, limits on parameters, etc.
void setRGBColor(char r, char g, char b) {
    r << 2;
    TB3CCR3 = r;
    g << 2;
    TB3CCR2 = g;
    b << 2;
    TB3CCR1 = b;
}