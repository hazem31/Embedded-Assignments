/*
 * gpio.c
 *
 * Created: 09/05/2022 04:44:28 م
 *  Author: hazem
 */ 

#include "Atmega32.h"
#include "gpio.h"


void MCAL_disable_Pull_up() 
{
	SFIOR |= (1<<2);
}
void MCAL_enable_Pull_up()
{
	SFIOR &= ~(1<<2);
}


void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig_t* PinConfig)
{
	
	if (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO)
	{
		GPIOx->DDR &= ~(PinConfig->GPIO_PinNumber);
		GPIOx->PORT &= ~(PinConfig->GPIO_PinNumber);		
	}
	else if (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
	{
		GPIOx->DDR &= ~(PinConfig->GPIO_PinNumber);
		GPIOx->PORT |= (PinConfig->GPIO_PinNumber);
	}
	else if (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP)
	{
		GPIOx->DDR |= (PinConfig->GPIO_PinNumber);
	}
}
void MCAL_GPIO_DeInit (GPIO_TypeDef *GPIOx)
{
	GPIOx->DDR = 0x00;
	GPIOx->PORT = 0x00;
}

uint8_t MCAL_GPIO_ReadPin (GPIO_TypeDef *GPIOx,uint8_t PinNumber )
{
	
	if((GPIOx->PIN & PinNumber) != GPIO_PIN_RESET  )
		return GPIO_PIN_SET;
	else
		return GPIO_PIN_RESET;
}
uint8_t MCAL_GPIO_ReadPort (GPIO_TypeDef *GPIOx)
{
	return GPIOx->PIN;
}

void MCAL_GPIO_WritePin (GPIO_TypeDef *GPIOx,uint8_t PinNumber , uint8_t Value)
{
	if (Value == GPIO_PIN_SET)
	{
		GPIOx->PORT |= PinNumber;
	}
	else
	{
		GPIOx->PORT &= ~(PinNumber);
	}
	
}
void MCAL_GPIO_WritePort (GPIO_TypeDef *GPIOx , uint8_t Value)
{
	GPIOx->PORT = Value;
}

void MCAL_GPIO_TogglePin (GPIO_TypeDef *GPIOx,uint8_t PinNumber )
{
	GPIOx->PORT ^= PinNumber;
	
}
