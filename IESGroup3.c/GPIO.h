// gpio.h
#ifndef GPIO_H_
#define GPIO_H_

#define ON  1
#define OFF 0

void init_GPIO(void);
void Solenoid(char state);
void Ign_LED(char state);
int get_call_for_heat(void);

#endif
