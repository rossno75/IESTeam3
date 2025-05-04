#include "msp430.h"
#include "sensors.h"


char ADCFinished = 0;
unsigned int ADCResult = 0;

// Thermistor, Thermocouple, and Potentiometer
// Thermocouple --> P1.3 (A3)
// Thermistor --> P1.4 (A4)
// Pot --> P1.5 (A5)

unsigned int readThermistor(){
    unsigned int result = 0;
    result = readADC(4);
    return result;
}

unsigned int readThermocouple(){
    unsigned int result = 0;
    result = readADC(3);
    return result;
}

unsigned int readPot(){
    unsigned int result = 0;
    result = readADC(5);
    return result;
}

void init_tc(){
  P1SEL0 |= BIT1 + BIT2 + BIT3;             // Select P1.1 P1.2 P1.3 OA function
  P1SEL1 |= BIT1 + BIT2 + BIT3;             // Select P1.1 P1.2 P1.3 OA function

  SAC0OA = NMUXEN + PMUXEN + PSEL_0 + NSEL_1;//Select positive and negative pin input
  SAC0OA |= OAPM;                           // Select low speed and low power mode
  SAC0PGA = GAIN0 + GAIN2 + MSEL_2;         // Set Non-inverting PGA mode with Gain=17
  SAC0OA |= SACEN + OAEN;                   // Enable SAC and OA
}

void initADC(){
    // Configure ADC Pins
    P1SEL0 |= BIT3 | BIT4 | BIT5;
    P1SEL1 |= BIT3 | BIT4 | BIT5;

    //Configure ADC
    ADCCTL0 |= ADCSHT_2 | ADCON;        // ADCON, S&H=16 ADC clks
    ADCCTL1 |= ADCSHP;                  // ADCCLK = MODOSC; sampling timer
    ADCCTL2 &= ~ADCRES;                 // clear ADCRES in ADCCTL
    ADCCTL2 |= ADCRES_2;                // 12-bit conversion results
    ADCIE |= ADCIE0;                    // Enable ADC conv complete interrupt

}



/*
SENSOR INTERRUPT ROUTINES
*/


unsigned int readADC(char Channel){
    
    switch(Channel){
        case 3:     ADCMCTL0 |= ADCINCH_3;
                    break;
        case 4:     ADCMCTL0 |= ADCINCH_4;
                    break;
        case 5:     ADCMCTL0 |= ADCINCH_5;
                    break;
        default:    ADCMCTL0 |= ADCINCH_3;
                    break;
    }
    
    
    ADCFinished = 0;
    ADCCTL0 |= ADCENC | ADCSC;          // Sampling and conversion start
    while(ADCFinished != 1);            // Wait until reading is finished
    return ADCResult;                   // Return the contents of ADCMEM0
}

// ADC interrupt service routine
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
{
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
    {
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG:
            break;
        case ADCIV_ADCTOVIFG:
            break;
        case ADCIV_ADCHIIFG:
            break;
        case ADCIV_ADCLOIFG:
            break;
        case ADCIV_ADCINIFG:
            break;
        case ADCIV_ADCIFG:
            ADCResult = ADCMEM0;
            ADCFinished = 1;
            break;
        default:
            break;
    }
}
 
 int flame_Detect(void)      { return readADC(3) > FLAME_THRESHOLD; }
