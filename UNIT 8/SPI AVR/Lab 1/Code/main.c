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
#include "spi.h"

uint16_t ch = 'k';

#define ACT_AS_MASTER
//#define ACT_AS_SLAVE

/*

void SPI_CALLBACK(void)
{
	#ifdef ACT_AS_SLAVE
	ch = 0x0f;
	MCAL_SPI_ReceiveData(SPI,&ch,Pollingdisable);
	MCAL_USART_Send(&ch,disable);
	#endif
}


void UART_CALLBACK_RXC(void)
{
	#ifdef ACT_AS_MASTER

	MCAL_USART_Receive(&ch , disable);
	//HCAL_LCD_WRITE_CHAR(ch);
	MCAL_USART_Send(&ch,enable);
	MCAL_GPIO_WritePin(GPIOB,SPI_SS_PIN,0);
	MCAL_SPI_SendData(SPI,&ch,Pollingdisable);
	MCAL_GPIO_WritePin(GPIOB,SPI_SS_PIN,1);
	#endif
}

*/

int main(void)
{
	
	SPI_Config SPIConfig;
	uint8_t ch_s = 255 , ch_r = 0;
	DDRA = 0xFF;
	
	/*
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
	*/
	SPIConfig.CLKPhase = SPI_Clock_Phase_SAMPLE_SECOND;
	SPIConfig.CLKPolarity = SPI_CLKPolarity_LEAD_FALLING;
	SPIConfig.Frame_Format = SPI_FRAME_FORMAT_MSB_transmmitted_first;
	SPIConfig.SPI_DOUBLE_SPEED = SPI_DOUBLE_ENABLE;
	SPIConfig.SPI_BAUDRATEPRESCALER = SPI_BAUDRATEPRESCALER_2;
	
	#ifdef ACT_AS_MASTER
		SPIConfig.Device_Mode = SPI_DEVICE_MODE_MASTER;
		SPIConfig.IRQ_Enable = SPI_DISABLE_IRQ;
		MCAL_SPI_Init(SPI,&SPIConfig);
		MCAL_SPI_GPIO_Set_Pins(SPI);
		
		
		
		for (ch_s = 0; ch_s <= 255; ch_s++)
		{
			_delay_ms(100);
			MCAL_GPIO_WritePin(GPIOB,SPI_SS_PIN,0);
			MCAL_SPI_TX_RX_UPDATED(SPI,&ch_s,&ch_r);
			MCAL_GPIO_WritePin(GPIOB,SPI_SS_PIN,1);
			PORTA = ch_r;
		}
		
	#endif
	
	#ifdef ACT_AS_SLAVE
	
		SPIConfig.Device_Mode = SPI_DEVICE_MODE_SLAVE;
		SPIConfig.IRQ_Enable = SPI_ENABLE_IRQ;
		SPIConfig.P_IRQ_CallBack = SPI_CALLBACK;
		//SPIConfig.IRQ_Enable = SPI_DISABLE_IRQ;
		MCAL_SPI_Init(SPI,&SPIConfig);
		MCAL_SPI_GPIO_Set_Pins(SPI);
		//MCAL_GPIO_WritePin(GPIOB,SPI_SS_PIN,1);
		
		/*
		for (ch_s = 255; ch_s >= 0; ch_s--)
		{
			MCAL_SPI_TX_RX_UPDATED(SPI,&ch_s , &ch_r);
			PORTA = ch_r;
		}
		*/
		
	#endif
	
	
	
	//HCAL_LCD_INIT();
	//HCAL_LCD_WRITE_CHAR('v');
	//_delay_ms(50);
	Interupt_Enable();
	
	while (1) 
    {

	}
}

