#include "servo.h"
#include "MSP430.h"
#include "msp430fr2355.h"

void Servo_Control(char state) {
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

    P2DIR |= BIT0;             // Set P2.0 as output
    P2SEL0 |= BIT0;            // Select timer function
    P2SEL1 &= ~BIT0;

    PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO high-impedance mode

    TB1CCR0 = 20000;           // PWM period
    TB1CCTL1 = OUTMOD_7;       // Reset/set mode
    TB1CCR1 = (state == '1') ? 1500 : 490; // Set pulse width (e.g., 1.5ms for ON, ~0.5ms for OFF)
    TB1CTL = TBSSEL__SMCLK | MC__UP; // SMCLK, up mode

//    __bis_SR_register(LPM3_bits); // Enter LPM3 (optional depending on usage)
}
