/*
 * mcal.c
 *
 * Created: 09/05/2022 01:21:10 م
 * Author : hazem
 */ 

#include <avr/io.h>

#include<avr/interrupt.h>
#include "Atmega32.h"
#include "gpio.h"
#include "keypad.h"
#include "lcd.h"
#include "EXTI.h"

/*
void gpio_init() {
	GPIO_PinConfig_t PinConfig;
	PinConfig.GPIO_PinNumber = GPIO_PIN_0;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(GPIOA,&PinConfig);	
	
	
	PinConfig.GPIO_PinNumber = GPIO_PIN_1;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(GPIOA,&PinConfig);
	
}
*/
unsigned int IRQ_FLAG = 0;


void Interupt_INT0(void)
{
	IRQ_FLAG = 1;
	HCAL_LCD_WRITE_STRING("INT0 is working");
	_delay_ms(5000);
}
/*
ISR(INT0_vect)
{
		IRQ_FLAG = 1;
		HCAL_LCD_WRITE_STRING("INT0 is working");
		_delay_ms(5000);	
}
*/
int main(void)
{
	EXTI_PinConfig_t EX;
	EX.EXTI_PIN = INT0_Falling;
	EX.IRQ_EN = EXTI_IRQ_Enable;
	EX.P_IRQ_callBack = Interupt_INT0; 
	MCAL_EXTI_GPIO_Init(&EX);
	Interupt_Enable();
	//MCUCR |= (1<<1);
	//GICR |= (1<<6);
	
	//SREG |= (1<<7);
	
	HCAL_LCD_INIT();
	HCAL_LCD_WRITE_CHAR('A');
	_delay_ms(1000);	
	HCAL_LCD_clear_screen();
	IRQ_FLAG = 1;
	while (1) 
    {
		if (IRQ_FLAG == 1)
		{
				HCAL_LCD_clear_screen();
				IRQ_FLAG = 0;
		}
		
		
    }
}

