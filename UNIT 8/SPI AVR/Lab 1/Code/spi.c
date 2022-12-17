/*
 * spi.c
 *
 * Created: 16/11/2022 10:20:02 م
 *  Author: hazem
 */ 

#include "spi.h"


SPI_Config* Global_SPI_Config_Pointer;
SPI_Config Global_SPI_Config;

void MCAL_SPI_Init(SPI_TypeDef* SPIx , SPI_Config* SPI_Config)
{
	uint8_t tempreg = 0;
	Global_SPI_Config = *(SPI_Config);
	Global_SPI_Config_Pointer = &Global_SPI_Config;
	
	tempreg |= (1<<6);
	
	tempreg |= SPI_Config->Device_Mode;
	
	tempreg |= SPI_Config->Frame_Format;
	
	tempreg |= SPI_Config->CLKPolarity;
	
	tempreg |= SPI_Config->CLKPhase;
	
	SPIx->SPSR_r |= SPI_Config->SPI_DOUBLE_SPEED;
	
	tempreg |= SPI_Config->SPI_BAUDRATEPRESCALER;
	
	tempreg |= SPI_Config->IRQ_Enable;
	
	SPIx->SPCR_r = tempreg;

}
void MCAL_SPI_Denit(SPI_TypeDef* SPIx)
{
	SPIx->SPCR_r = 0;
	SPIx->SPSR_r &= ~(1<<0);
	
}

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx)
{
	GPIO_PinConfig_t PINConfig;
	if (Global_SPI_Config_Pointer->Device_Mode == SPI_DEVICE_MODE_MASTER)
	{
		PINConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		PINConfig.GPIO_PinNumber = SPI_SCK_PIN;
		MCAL_GPIO_Init(SPI_GPIO_PORT,&PINConfig);
		
		PINConfig.GPIO_PinNumber = SPI_MOSI_PIN;
		PINConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		MCAL_GPIO_Init(SPI_GPIO_PORT,&PINConfig);
		
		PINConfig.GPIO_PinNumber = SPI_SS_PIN;
		PINConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		MCAL_GPIO_Init(SPI_GPIO_PORT,&PINConfig);
		
	
	}
	else
	{
		PINConfig.GPIO_PinNumber = SPI_MISO_PIN;
		PINConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		MCAL_GPIO_Init(SPI_GPIO_PORT,&PINConfig);
		
		
	}
	
}
void MCAL_SPI_SendData(SPI_TypeDef* SPIx , uint8_t * pTxBuffer , SPI_Polling_Mechanism PollingEn)
{
	if (PollingEn == Pollingenable)
		while(!(SPIx->SPSR_r & (1<<7)));
		
	
	SPIx->SPDR_r = *pTxBuffer;
	
}
void MCAL_SPI_ReceiveData(SPI_TypeDef* SPIx , uint8_t * pTxBuffer ,  SPI_Polling_Mechanism PollingEn)
{
	if (PollingEn == Pollingenable)
		while(!(SPIx->SPSR_r & (1<<7)));
	
	*pTxBuffer = SPIx->SPDR_r;
	
}
void MCAL_SPI_TX_RX(SPI_TypeDef* SPIx , uint8_t * pTxBuffer , SPI_Polling_Mechanism PollingEn)
{
	if (PollingEn == Pollingenable)
		while(!(SPIx->SPSR_r & (1<<7)));
	
	SPIx->SPDR_r = *pTxBuffer;
	
	if (PollingEn == Pollingenable)
		while(!(SPIx->SPSR_r & (1<<7)));
		
	*pTxBuffer = SPIx->SPDR_r;
}

void MCAL_SPI_TX_RX_UPDATED(SPI_TypeDef* SPIx , uint8_t * pTxBuffer1 , uint8_t * pTxBuffer2)
{
	SPIx->SPDR_r = *pTxBuffer1;
	while(!(SPIx->SPSR_r & (1<<7)));
	*pTxBuffer2 = SPIx->SPDR_r;
}

ISR(SPI_STC_vect)
{
	Global_SPI_Config_Pointer->P_IRQ_CallBack();
}