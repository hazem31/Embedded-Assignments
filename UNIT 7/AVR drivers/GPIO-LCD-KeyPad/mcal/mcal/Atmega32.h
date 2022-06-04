/*
 * Atmega32.h
 *
 * Created: 09/05/2022 01:35:29 م
 *  Author: hazem
 */ 


#ifndef ATMEGA32_H_
#define ATMEGA32_H_

#include <avr/io.h>
#include <stdint.h>
#define F_CPU 8000000UL
#include <util/delay.h>

// GPIO related ref

#define GPIOA_Base 0x39UL 
#define GPIOB_Base 0x36UL
#define GPIOC_Base 0x33UL
#define GPIOD_Base 0x30UL


typedef struct
{
	volatile uint8_t  PIN ;
	volatile uint8_t  DDR ;
	volatile uint8_t  PORT ;
}GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *)GPIOA_Base)
#define GPIOB ((GPIO_TypeDef *)GPIOB_Base)
#define GPIOC ((GPIO_TypeDef *)GPIOC_Base)
#define GPIOD ((GPIO_TypeDef *)GPIOD_Base)




#endif /* ATMEGA32_H_ */