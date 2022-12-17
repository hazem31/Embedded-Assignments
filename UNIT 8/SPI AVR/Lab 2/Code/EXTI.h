/*
 * EXTI.h
 *
 * Created: 03/06/2022 05:31:45 م
 *  Author: hazem
 */ 


#ifndef EXTI_H_
#define EXTI_H_


#include<avr/interrupt.h>
#include "Atmega32.h"
#include "gpio.h"


typedef struct
{
	uint8_t ETI_InputLineNumber ;
	GPIO_TypeDef *  GPIO_PORT;
	uint16_t GPIO_PIN ;
	uint8_t IVT_IRQ_Number;
	uint8_t Trigger_Case; // @ref Cases
	
	
}EXTI_GPIO_Mapping_Config_t;

typedef struct
{
	EXTI_GPIO_Mapping_Config_t EXTI_PIN ; // specifies the external interrupt GPIO mapping , @ref EXTI_define

	void(* P_IRQ_callBack)(void); // set the c function to be called once the IRQ happen

	uint8_t IRQ_EN;

}EXTI_PinConfig_t;

#define EXTI0 0 // INT 0
#define EXTI1 1
#define EXTI2 2

// @ref EXTI_Trigger
#define EXTI_Trigger_LowLevel   			0
#define EXTI_Trigger_RisingAndFalling   	1
#define EXTI_Trigger_FALLING   				2
#define EXTI_Trigger_RISING   				3

#define EXTI_Trigger_RISING_INT2		1
#define EXTI_Trigger_FALLING_INT2		0


#define EXTI_IRQ_Enable 1
#define EXTI_IRQ_Disable 0


#define INT0_Rising						(EXTI_GPIO_Mapping_Config_t){EXTI0, GPIOD , GPIO_PIN_2 , INT0_IRQ , EXTI_Trigger_RISING }
#define INT0_Falling					(EXTI_GPIO_Mapping_Config_t){EXTI0, GPIOD , GPIO_PIN_2 , INT0_IRQ , EXTI_Trigger_FALLING }
#define INT0_RisingAndFalling			(EXTI_GPIO_Mapping_Config_t){EXTI0, GPIOD , GPIO_PIN_2 , INT0_IRQ , EXTI_Trigger_RisingAndFalling }
#define INT0_LowLevel					(EXTI_GPIO_Mapping_Config_t){EXTI0, GPIOD , GPIO_PIN_2 , INT0_IRQ , EXTI_Trigger_LowLevel }

#define INT1_Rising						(EXTI_GPIO_Mapping_Config_t){EXTI1, GPIOD , GPIO_PIN_3 , INT1_IRQ , EXTI_Trigger_RISING }
#define INT1_Falling					(EXTI_GPIO_Mapping_Config_t){EXTI1, GPIOD , GPIO_PIN_3 , INT1_IRQ , EXTI_Trigger_FALLING }
#define INT1_RisingAndFalling			(EXTI_GPIO_Mapping_Config_t){EXTI1, GPIOD , GPIO_PIN_3 , INT1_IRQ , EXTI_Trigger_RisingAndFalling }
#define INT1_LowLevel					(EXTI_GPIO_Mapping_Config_t){EXTI1, GPIOD , GPIO_PIN_3 , INT1_IRQ , EXTI_Trigger_LowLevel }

#define INT2_Rising						(EXTI_GPIO_Mapping_Config_t){EXTI2, GPIOB , GPIO_PIN_2 , INT2_IRQ , EXTI_Trigger_RISING_INT2 }
#define INT2_Falling					(EXTI_GPIO_Mapping_Config_t){EXTI2, GPIOB , GPIO_PIN_2 , INT2_IRQ , EXTI_Trigger_FALLING_INT2 }


void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t * EXTI_Config);
void MCAL_EXTI_GPIO_DeInit(void);

void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t * EXTI_Config);




#endif /* EXTI_H_ */