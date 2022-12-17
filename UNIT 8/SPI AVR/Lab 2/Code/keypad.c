/*
 * keypad.c
 *
 * Created: 17/05/2022 09:37:12 م
 *  Author: hazem
 */ 

#include "keypad.h"

uint8_t rows[] = {R0,R1,R2,R3};
uint8_t cols[] = {C0,C1,C2,C3};

void HCAL_Keypad_init()
{
	GPIO_PinConfig_t PinConfig;
	
	PinConfig.GPIO_PinNumber = R0;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init( KEYPAD_PORT ,&PinConfig);
	
	PinConfig.GPIO_PinNumber = R1;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init( KEYPAD_PORT ,&PinConfig);
	
	PinConfig.GPIO_PinNumber = R2;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init( KEYPAD_PORT ,&PinConfig);
	
	PinConfig.GPIO_PinNumber = R3;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init( KEYPAD_PORT ,&PinConfig);
	
	PinConfig.GPIO_PinNumber = C0;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init( KEYPAD_PORT ,&PinConfig);
	
	PinConfig.GPIO_PinNumber = C1;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init( KEYPAD_PORT ,&PinConfig);
	
	PinConfig.GPIO_PinNumber = C2;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init( KEYPAD_PORT ,&PinConfig);
	
	
	PinConfig.GPIO_PinNumber = C3;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init( KEYPAD_PORT ,&PinConfig);
}


char HCAL_Keypad_getkey()
{
	uint8_t i , j;
	for(i = 0 ; i < NROWS ; i++)
	{
		
		MCAL_GPIO_WritePin(KEYPAD_PORT,cols[0],GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT,cols[1],GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT,cols[2],GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT,cols[3],GPIO_PIN_SET);
		
		MCAL_GPIO_WritePin(KEYPAD_PORT,cols[i],GPIO_PIN_RESET);
		for (j = 0 ; j < NCOLS ; j++)
		{
			if (MCAL_GPIO_ReadPin(KEYPAD_PORT,rows[j]) == GPIO_PIN_RESET)
			{
				while(MCAL_GPIO_ReadPin(KEYPAD_PORT,rows[j]) == GPIO_PIN_RESET);
				switch (i) {
					case (0):
					if (j == 0)
					return '7';
					else if (j == 1)
					return '4';
					else if (j == 2)
					return '1';
					else if (j == 3)
					return '?';
					break;
					case (1):
					if (j == 0)
					return '8';
					else if (j == 1)
					return '5';
					else if (j == 2)
					return '2';
					else if (j == 3)
					return '0';
					break;
					case (2):
					if (j == 0)
					return '9';
					else if (j == 1)
					return '6';
					else if (j == 2)
					return '3';
					else if (j == 3)
					return '=';
					break;
					case (3):
					if (j == 0)
					return '/';
					else if (j == 1)
					return '*';
					else if (j == 2)
					return '-';
					else if (j == 3)
					return '+';
					break;
				}

			}
		}
	}
	
	return 'A';
}
