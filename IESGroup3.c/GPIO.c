// Solenoid, Igniter, and Call for Heat Signals
#include <msp430.h>
#include "GPIO.h"

#define heat_threshold 2.9

void init_GPIO(void)
{
    P5DIR |= BIT0 | BIT4;
    P3DIR &= ~BIT1;
    P3REN |= BIT1;
    P3OUT |= BIT1;
}

void Solenoid(char state)
{
    if (state == ON)
        P5OUT |= BIT0;
    else
        P5OUT &= ~BIT0;
}

void Ign_LED(char state)
{
    if (state == ON)
        P5OUT |= BIT4;
    else
        P5OUT &= ~BIT4;
}

int get_call_for_heat(void)
{
    return (P3IN & BIT1);
}
