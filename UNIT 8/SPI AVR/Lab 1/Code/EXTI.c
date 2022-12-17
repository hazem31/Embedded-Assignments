/*
 * EXTI.c
 *
 * Created: 03/06/2022 05:31:59 م
 *  Author: hazem
 */ 

#include "Atmega32.h"
#include "EXTI.h"
#include "gpio.h"


void(* GP_IRQ_callBack[3])(void);


#define EXTI_Mapping_Register(x)     ( (x == EXTI0 || x == EXTI1) ? &(EXTI->MCUCR_r) : &(EXTI->MCUCSR_r) )


#define EXTI_Mapping_postion(x)     ( (x == EXTI0 ) ? 0 : (x == EXTI1)  ?  2 : 6 )

#define EXTI_Enable_position(x)		((x == EXTI0 ) ?  6 : (x == EXTI1)  ?  7 : 5)

void Update_EXTI(EXTI_PinConfig_t * EXTI_Config)
{
	// 1 - Config GPIO as input floating
	GPIO_PinConfig_t PinConfig;
	PinConfig.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_PORT,&PinConfig);
	
	// 2 position
	volatile uint8_t * Config_register = EXTI_Mapping_Register(EXTI_Config->EXTI_PIN.ETI_InputLineNumber); 
	volatile uint8_t position = EXTI_Mapping_postion(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	
	// 3 config
	if (Config_register == &(EXTI->MCUCR_r))
	{
		*Config_register &= ~(0b11 << position);
	}
	else
	{
		*Config_register &= ~(1 << position);
	}
	
	*Config_register |= ( EXTI_Config->EXTI_PIN.Trigger_Case << position);
	
	// 4 call back function 
	GP_IRQ_callBack[EXTI_Config->EXTI_PIN.ETI_InputLineNumber] = EXTI_Config->P_IRQ_callBack;
	
	// 5 -ENable
	volatile uint8_t Enable_position =  EXTI_Enable_position(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	if (EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->GICR_r |= (1<<Enable_position);
	}
	else
	{
		EXTI->GICR_r &= ~(1<<Enable_position);
	}
	
}
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t * EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}
void MCAL_EXTI_GPIO_DeInit(void)
{
	EXTI->GICR_r &= ~(0b111<<5);
	EXTI->GIFR_r &= ~(0b111<<5);
	EXTI->MCUCSR_r &= ~(1<<6);
	EXTI->MCUCSR_r &= ~(0x0F);
}

void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t * EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}

ISR (INT0_vect)          //External interrupt_zero ISR
{
	GP_IRQ_callBack[0]();
	// EXTI->GIFR_r |= (1<<6) cleared by sw
}
ISR (INT1_vect)        //External interrupt_one ISR
{
	GP_IRQ_callBack[1]();
}
ISR (INT2_vect)        //External interrupt_one ISR
{
	GP_IRQ_callBack[2]();
}

