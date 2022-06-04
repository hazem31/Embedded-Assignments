/*
 * mcal.c
 *
 * Created: 09/05/2022 01:21:10 م
 * Author : hazem
 */ 

#include <avr/io.h>

#include "Atmega32.h"
#include "gpio.h"
#include "keypad.h"
#include "lcd.h"

void gpio_init() {
	GPIO_PinConfig_t PinConfig;
	PinConfig.GPIO_PinNumber = GPIO_PIN_0;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(GPIOA,&PinConfig);	
	
	
	PinConfig.GPIO_PinNumber = GPIO_PIN_1;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(GPIOA,&PinConfig);
	
}

int main(void)
{
	char key;
	gpio_init();
	HCAL_Keypad_init();
	HCAL_LCD_INIT();	
	/* Replace with your application code */
    while (1) 
    {
		key = HCAL_Keypad_getkey();
		if (key != 'A')
		{
			if (key == '?')
				HCAL_LCD_clear_screen();
			else
				HCAL_LCD_WRITE_CHAR(key);
		}
		if(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) == GPIO_PIN_RESET)
		{
			MCAL_GPIO_TogglePin(GPIOA,GPIO_PIN_0);
			while(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) == 0);
		}
		
		
    }
}

