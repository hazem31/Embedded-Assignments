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
#include "usart.h"


uint16_t ch = 'k';

void UART_CALLBACK_RXC(void)
{
	MCAL_USART_Receive(&ch , disable);
	HCAL_LCD_WRITE_CHAR(ch);
}

int main(void)
{
	//volatile uint16_t  data;
	
	USART_Config Uscfg;
	Uscfg.IRQ_CallBack = Default_IRQ_UART;
	Uscfg.IRQ_CallBack.P_IRQ_CallBack_RXC = UART_CALLBACK_RXC;
	Uscfg.BAUD_RATE_UBRR = 51;
	Uscfg.Mode_Operation = USART_MODE_Normal_Asynchronous;
	Uscfg.Data_bits = DATA_BITS_8;
	Uscfg.Parity_Mode = PARITY_DISABLED;
	Uscfg.Stop_bit = STOP_ONE_BIT;
	Uscfg.TX_RX_ENABLE = ENABLE_TX_RX;
	MCAL_USART_Init(&Uscfg);
	HCAL_LCD_INIT();
	HCAL_LCD_WRITE_CHAR('v');
	_delay_ms(50);
	Interupt_Enable();
	/*
	MCAL_USART_Send_Blocking((uint16_t)'M');
	_delay_ms(50);
	MCAL_USART_Send_Blocking((uint16_t)'Y');
	_delay_ms(50);
	MCAL_USART_Send_Blocking((uint16_t)'N');
	_delay_ms(50);
	*/
	while (1) 
    {
		//MCAL_USART_Receive(&ch , enable);
		//MCAL_USART_Send(&ch , enable);
		//HCAL_LCD_WRITE_CHAR(ch);
	}
}

