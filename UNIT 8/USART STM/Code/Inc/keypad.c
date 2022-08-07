/*
 * keypad.c
 *
 * Created: 4/22/2021 6:32:10 PM
 *  Author: Marco
 */

#include "keypad.h"

uint16_t Key_padRow[] = {R0 , R1 , R2 , R3};
uint16_t Key_padCol[] = {C0 , C1 , C2 , C3};

void delay_mss(uint32_t time) {
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++)
			;
}

void Keypad_init() {

	GPIO_PinConfig_t PinConfig;

	PinConfig.GPIO_PinNumber = R0;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = R1;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);


	PinConfig.GPIO_PinNumber = R2;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = R3;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = C0;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = C1;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);


	PinConfig.GPIO_PinNumber = C2;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = C3;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);


}


char Keypad_getkey() {
	uint8_t i,j ;

	for(i = 0 ; i < NROWS ; i++)
	{
		MCAL_GPIO_WritePin(KEYPAD_PORT, C0 , GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, C1 , GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, C2 , GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, C3 , GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[i] , GPIO_PIN_RESET);
		for( j = 0 ; j < NCOLS ; j++)
		{
			if(MCAL_GPIO_ReadPin(KEYPAD_PORT, Key_padRow[j]) == 0)
			{
				while (MCAL_GPIO_ReadPin(KEYPAD_PORT, Key_padRow[j]) == 0);
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
