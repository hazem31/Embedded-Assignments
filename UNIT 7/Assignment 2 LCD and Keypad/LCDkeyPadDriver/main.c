/*
 * LCDkeyPadDriver.c
 *
 * Created: 07/04/2022 02:42:18 م
 * Author : hazem
 */ 

#include <avr/io.h>
#include "LCD/lcd.h"
#include "Keypad/keypad.h"

int main(void)
{
	volatile char key;
    /* Replace with your application code */
    LCD_lcd_init();
	Keypad_init();
	LCD_Send_A_Character('s');
	while (1) 
    {
		key = Keypad_getkey();
		switch(key)
		{
			case 'A':
			{
				break;	
			}
			case '?':
			{
				LCD_clear_screen();
				break;
			}
			default: 
			{
				LCD_Send_A_Character(key);		
			}
			
		}	
    }
}

