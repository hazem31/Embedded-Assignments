


#ifndef INC_STM32F103C6_H_
#define INC_STM32F103C6_H_


//-------------------------------------------------------------------------------------------
//Includes
//-------------------------------------------------------------------------------------------

#include "stdlib.h"
#include <stdint.h>


//-------------------------------------------------------------------------------------------
//Base addresses for memory
//-------------------------------------------------------------------------------------------

#define FLASH_MEMORY_BASE   					0x08000000UL
#define System_MEMORY_BASE  					0x1FFFF000UL
#define SRAM_MEMORY_BASE    					0x20000000UL

#define Peripherals_BASE    					0x40000000UL
#define Cortex_M3_Internal_Peripherals_BASE     0x40000000UL

//-------------------------------------------------------------------------------------------
//Base addresses for AHB BUS Peripherals
//-------------------------------------------------------------------------------------------

#define RCC_BASE								(Peripherals_BASE + 0x00021000UL)

//-------------------------------------------------------------------------------------------
//Base addresses for APB2 BUS Peripherals
//-------------------------------------------------------------------------------------------

//for GPIO

#define GPIOA_BASE								0x40010800UL
#define GPIOB_BASE								0x40010C00UL
#define GPIOC_BASE								0x40011000UL
#define GPIOD_BASE								0x40011400UL
#define GPIOE_BASE								0x40011800UL

// for EXIT

#define EXTI_BASE								0x40010400UL
#define AFIO_BASE								0x40010000UL
// for AFIO


//-------------------------------------------------------------------------------------------
//Base addresses for APB1 BUS Peripherals
//-------------------------------------------------------------------------------------------


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripherals Registers
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripherals Registers : GPIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;

}GPIO_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripherals Registers : RCC
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;

}RCC_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripherals Registers : EXTI
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RSTR;
	volatile uint32_t FSTR;
	volatile uint32_t SWIER;
	volatile uint32_t BR;

}EXTI_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripherals Registers : AFIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RESERVED0;
	volatile uint32_t MAPR2;

}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripherals Registers : INSTANTS
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


#define GPIOA 							((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB 							((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC 							((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD 							((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE 							((GPIO_TypeDef *) GPIOE_BASE)

#define RCC								((RCC_TypeDef  *) RCC_BASE)

#define AFIO							((AFIO_TypeDef  *) AFIO_BASE)

#define EXTI							((EXTI_TypeDef  *) EXTI_BASE)


#define RCC_GPIOA_CLK_EN() 			(RCC->APB2ENR |= (1<<2))
#define RCC_GPIOB_CLK_EN() 			(RCC->APB2ENR |= (1<<3))
#define RCC_GPIOC_CLK_EN() 			(RCC->APB2ENR |= (1<<4))
#define RCC_GPIOD_CLK_EN() 			(RCC->APB2ENR |= (1<<5))
#define RCC_GPIOE_CLK_EN() 			(RCC->APB2ENR |= (1<<6))

#define AFIO_CLK_EN() 				(RCC->APB2ENR |= (1<<0))


#endif
