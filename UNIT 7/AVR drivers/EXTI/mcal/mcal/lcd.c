/*
 * lcd.c
 *
 * Created: 17/05/2022 10:33:20 م
 *  Author: hazem
 */ 

#include "lcd.h"

void Make_Pins_Output()
{
		GPIO_PinConfig_t PinCfg;
		PinCfg.GPIO_PinNumber = DATA_PIN_0;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);

		PinCfg.GPIO_PinNumber = DATA_PIN_1;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
		
		
		PinCfg.GPIO_PinNumber = DATA_PIN_2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
		
		
		PinCfg.GPIO_PinNumber = DATA_PIN_3;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
		
		PinCfg.GPIO_PinNumber = DATA_PIN_4;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
		
		PinCfg.GPIO_PinNumber = DATA_PIN_5;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
		
		PinCfg.GPIO_PinNumber = DATA_PIN_6;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
		
		PinCfg.GPIO_PinNumber = DATA_PIN_7;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
}

void Make_Pins_Input()
{
		GPIO_PinConfig_t PinCfg;
		PinCfg.GPIO_PinNumber = DATA_PIN_0;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);

		PinCfg.GPIO_PinNumber = DATA_PIN_1;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
		
		
		PinCfg.GPIO_PinNumber = DATA_PIN_2;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
		
		
		PinCfg.GPIO_PinNumber = DATA_PIN_3;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
		
		PinCfg.GPIO_PinNumber = DATA_PIN_4;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
		
		PinCfg.GPIO_PinNumber = DATA_PIN_5;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
		
		PinCfg.GPIO_PinNumber = DATA_PIN_6;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
		
		PinCfg.GPIO_PinNumber = DATA_PIN_7;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_DATA, &PinCfg);
}

void HCAL_LCD_INIT()
{
	GPIO_PinConfig_t PinCfg;
	
	_delay_ms(15);
	
	PinCfg.GPIO_PinNumber = RS_SWITCH;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = RW_SWITCH;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = EN_SWITCH;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);
	
	
	Make_Pins_Output();

	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	
	_delay_ms(15);
	
	HCAL_LCD_clear_screen();
	HCAL_LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	HCAL_LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	HCAL_LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	HCAL_LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);

}


void HCAL_LCD_WRITE_COMMAND(unsigned char command)
{
	MCAL_GPIO_WritePort(LCD_DATA, command);
	
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	_delay_ms(1);
	HCAL_LCD_lcd_kick();
	
}
void HCAL_LCD_WRITE_CHAR(unsigned char character)
{
	MCAL_GPIO_WritePort(LCD_DATA, character);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);
	_delay_ms(1);
	HCAL_LCD_lcd_kick();
	
	
}
void HCAL_LCD_WRITE_STRING(char* string)
{
	int count = 0;
	while (*string > 0) {
		count++;
		HCAL_LCD_WRITE_CHAR(*string++);
		if (count == 16) {
			HCAL_LCD_GOTO_XY(2, 0);
			} else if (count == 32) {
			HCAL_LCD_clear_screen();
			HCAL_LCD_GOTO_XY(1, 0);
			count = 0;
		}
	}
	
	
}
void HCAL_LCD_check_lcd_isbusy(void)
{
	
	Make_Pins_Input();
	
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	HCAL_LCD_lcd_kick();
	Make_Pins_Output();
	MCAL_GPIO_TogglePin(GPIOA,GPIO_PIN_0);
}
void HCAL_LCD_lcd_kick(void)
{
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
	_delay_ms(50);
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_SET);
}
void HCAL_LCD_clear_screen()
{
	HCAL_LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
	
}
void HCAL_LCD_GOTO_XY(unsigned char line, unsigned char position)
{
	if (line == 1) {
		if (position < 16 && position >= 0) {
			HCAL_LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW + position);
		}
	}
	if (line == 2) {
		if (position < 16 && position >= 0) {
			HCAL_LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW + position);
		}
	}

}
