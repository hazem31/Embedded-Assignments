/*
 * keypad.h
 *
 * Created: 09/05/2022 06:01:01 م
 *  Author: hazem
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "gpio.h"

#define KEYPAD_PORT GPIOB

#define NROWS 4

#define NCOLS 4

#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_2
#define R3 GPIO_PIN_3
#define C0 GPIO_PIN_4
#define C1 GPIO_PIN_5
#define C2 GPIO_PIN_6
#define C3 GPIO_PIN_7

void HCAL_Keypad_init();
char HCAL_Keypad_getkey();


#endif /* KEYPAD_H_ */