/*
 * lcd.c
 *
 * Created: 07/04/2022 02:44:16 م
 *  Author: hazem
 */ 


#include "lcd.h"

void LCD_lcd_kick (void)
{
	LCD_control &= ~ (1<<EN_switch);
	_delay_ms(50) ;
	LCD_control |= 1<<EN_switch;
}


void LCD_check_lcd_isbusy(void)
{
	DataDir_LCD_port &= ~(0xff<<DATA_shift) ; // making it as input 
	LCD_control |= (1<<ReadWrite); // read
	LCD_control &= ~ (1<<RS_switch); // sending command so rs is off

	//	while (LCD_port >= 0x80)
	//	{
	LCD_lcd_kick (); // just like checking the p7 for busy so instead we make a delay 
	//	}

	//	_delay_ms (500) ;
	DataDir_LCD_port = 0xFF; //0xFF means 0b11111111 means output 
	LCD_control &= ~ (1<<ReadWrite); //enable write
}


void LCD_GotoXY(unsigned char line, unsigned char position )
{
	if (line == 0)
	{
		if ( position < 16 && position >= 0)
		{
			LCD_Send_A_Command(0x80+position);
		}
	}
	else if (line == 1)
	{
		if ( position < 16 && position >= 0)
		{
			LCD_Send_A_Command(0xC0+position);
		}
	}
	
}



void LCD_lcd_init(void){
	
_delay_ms(20);
DataDir_LCD_control |= (1<<EN_switch | 1<<ReadWrite | 1<<RS_switch) ;
LCD_control &= ~(1<<EN_switch | 1<<ReadWrite | 1<<RS_switch) ;

DataDir_LCD_port = 0xff ;
_delay_ms(15);

LCD_clear_screen ();

#ifdef EIGHT_BIT_MODE
LCD_Send_A_Command(LCD_FUNCTION_8BIT_2LINES);

#endif
#ifdef FOUR_BIT_MODE
LCD_Send_A_Command(0x02);

LCD_Send_A_Command(LCD_FUNCTION_4BIT_2LINES);

#endif

LCD_Send_A_Command(LCD_ENTRY_MODE);
LCD_Send_A_Command(LCD_BEGIN_AT_FIRST_RAW);
LCD_Send_A_Command(LCD_DISP_ON_CURSOR_BLINK);

}


void LCD_clear_screen(void) {
	LCD_Send_A_Command(LCD_CLEAR_SCREEN);		
}

void LCD_Send_A_Command(unsigned char command){
	
#ifdef EIGHT_BIT_MODE
LCD_check_lcd_isbusy();

LCD_port = command  ;
LCD_control &= ~ ((1<<ReadWrite)|(1<<RS_switch));
LCD_lcd_kick ();
//LCD_port = 0;
#endif
#ifdef FOUR_BIT_MODE
LCD_check_lcd_isbusy();

LCD_control &= ~ ((1<<ReadWrite)|(1<<RS_switch));
LCD_port = (LCD_port & 0x0F) | (command & 0xF0);
//LCD_VoidLcd_waitIfBusy();
//SET_DATA_DIRECTION_REGISTER(LCD_DATA_DIRECTION_PORT, PORT_OUTPUT_DIRECTION);
//LCD_SET_REGISTER_SELECT(LCD_REGISTER_SELECT_DISABLE);
//	LCD_SET_READ_WRITE(WRITE_TO_LCD);
//LCD_VoidLcd_referish();
LCD_lcd_kick ();
LCD_port = (LCD_port & 0x0F) | (command << 4);
//LCD_VoidLcd_waitIfBusy();
//LCD_VoidLcd_referish();
LCD_lcd_kick ();
#endif
	
	
}


void LCD_Send_A_Character(unsigned char character)
{
	
#ifdef EIGHT_BIT_MODE
LCD_check_lcd_isbusy();

LCD_control |= 1<<RS_switch; //turn RS ON for Data mode.
LCD_port = ( ( (character  ) << DATA_shift)   )  ;
LCD_control |= 1<<RS_switch; //turn RS ON for Data mode.
LCD_control &= ~ (1<<ReadWrite);//turn RW off so you can write.


LCD_lcd_kick ();
//LCD_port = 0;
#endif

#ifdef FOUR_BIT_MODE
LCD_port = (LCD_port & 0x0F) | (character & 0xF0);
LCD_control |= 1<<RS_switch; //turn RS ON for Data mode.
LCD_control &= ~ (1<<ReadWrite);//turn RW off so you can write.
LCD_lcd_kick ();
LCD_port = (LCD_port & 0x0F) | (character << 4);
LCD_control |= 1<<RS_switch; //turn RS ON for Data mode.
LCD_control &= ~ (1<<ReadWrite);//turn RW off so you can write.
LCD_lcd_kick ();

#endif	
	
}


void LCD_Send_A_String(char *StringOfCharacters)
{
	LCD_clear_screen();
	LCD_GotoXY(LCD_FIRST_LINE,0);
	int count = 0;
	while(*StringOfCharacters != '\0')
	{
		count++;
		LCD_Send_A_Character(*StringOfCharacters++);
		if(count == 15)
		{
			LCD_GotoXY(LCD_SECOND_LINE,0);
		}
	}
	
}

