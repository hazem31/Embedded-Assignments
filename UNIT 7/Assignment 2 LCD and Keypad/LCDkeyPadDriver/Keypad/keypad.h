﻿/*
 * keypad.h
 *
 * Created: 20/04/2022 05:45:49 م
 *  Author: hazem
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include<util/delay.h>



//Keypad Information
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

#define keypadPORT PORTD
#define keypadPIN PIND
#define keypadDDR DDRD


//Keypad functions and global variables



void  Keypad_init();
char Keypad_getkey();



#endif /* KEYPAD_H_ */