// Potentiometer, Thermistor, Thermocouple
#include <msp430.h>
#include "ADC.h"

#define FLAME_THRESHOLD 0 // Adjustable!!

void init_ADC(void) // Initialize ADC
{
    P1SEL0 |= BIT3 | BIT4 | BIT5;
    ADCCTL0 = ADCSHT_2 | ADCON;
    ADCCTL1 = ADCSHP;
    ADCCTL2 = ADCRES;
}

int read_ADC(char channel)
{
    ADCMCTL0 = channel;
    ADCCTL0 |= ADCENC | ADCSC;
    while (!(ADCIFG & ADCIFG0));
    return ADCMEM0;
}

int therm_Read(void)        { return read_ADC(5); }
int read_potentiometer(void) { return read_ADC(4); }
int flame_Detect(void)      { return read_ADC(3) > FLAME_THRESHOLD; }
