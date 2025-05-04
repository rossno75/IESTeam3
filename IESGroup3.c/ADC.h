// adc.h
#ifndef ADC_H_
#define ADC_H_

void init_ADC(void);
int read_ADC(char channel);
int therm_Read(void);
int read_potentiometer(void);
int flame_Detect(void);

#endif
