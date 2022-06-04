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

#define SREG_Base 0x5FUL

#define EXTI_Base 0x54UL 

typedef struct
{
	volatile uint8_t  PIN ;
	volatile uint8_t  DDR ;
	volatile uint8_t  PORT ;
}GPIO_TypeDef;

typedef struct  
{
	volatile uint8_t MCUCSR_r;
	volatile uint8_t MCUCR_r;
	volatile uint8_t reserved[4];
	volatile uint8_t GIFR_r ;
	volatile uint8_t GICR_r ;
}EXTI_TypeDef;

#define GPIOA ((GPIO_TypeDef *)GPIOA_Base)
#define GPIOB ((GPIO_TypeDef *)GPIOB_Base)
#define GPIOC ((GPIO_TypeDef *)GPIOC_Base)
#define GPIOD ((GPIO_TypeDef *)GPIOD_Base)

#define SREG_r	*(volatile uint8_t *)(SREG_Base)

#define EXTI ((EXTI_TypeDef *)EXTI_Base)


//-*-*-*-*-*-*-*-*-*-*-*-
//Macros :
//-*-*-*-*-*-*-*-*-*-*-*

#define Interupt_Enable() (SREG_r |= (1<<7));
#define Interupt_Disable() (SREG_r &= ~(1<<7));

//-*-*-*-*-*-*-*-*-*-*-*-
//IVT :
//-*-*-*-*-*-*-*-*-*-*-*
//EXTI
#define INT0_IRQ 2
#define INT1_IRQ 3
#define INT2_IRQ 4 

#endif /* ATMEGA32_H_ */