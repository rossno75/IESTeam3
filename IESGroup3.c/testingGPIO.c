#include <msp430.h>
#include "GPIO.h"
#include "intrinsics.h"
#include "servo.h"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;

    init_GPIO();
    while(1){

   Servo_Control(ON)
    __delay_cycles(500000);

    Servo_Control(OFF);
    __delay_cycles(500000);

    }
}