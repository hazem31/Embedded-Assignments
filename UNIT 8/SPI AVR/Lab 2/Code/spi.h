/*
 * spi.h
 *
 * Created: 16/11/2022 10:20:16 م
 *  Author: hazem
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "Atmega32.h"
#include "gpio.h"

#define SPI_GPIO_PORT	GPIOB
#define SPI_SS_PIN		GPIO_PIN_4
#define SPI_MOSI_PIN	GPIO_PIN_5
#define SPI_MISO_PIN	GPIO_PIN_6
#define SPI_SCK_PIN		GPIO_PIN_7

#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7

#define SPI_SPIF		(uint8_t)(0x80)

typedef struct
{
	uint8_t Device_Mode; // master or slave @ref SPI_DEVICE_MODE
	uint8_t Frame_Format; // LSB or MSB first @ref SPI_FRAME_FORMAT
	uint8_t CLKPolarity; // idle high or low @ref SPI_POLARITY
	uint8_t CLKPhase; //  sample edge  @SPI_CLKPhase
	uint8_t SPI_BAUDRATEPRESCALER; // clk freq @ref SPI_BAUD
	uint8_t SPI_DOUBLE_SPEED; // @ref SPI_DOUBLE 
	uint8_t IRQ_Enable; // enable interrupt @ref SPI_IRQ
	
	void(* P_IRQ_CallBack)(void); 
	
}SPI_Config;

//=================================================
//=====================Refrence Macros ============
//================================================

// @ref SPI_DEVICE_MODE
#define SPI_DEVICE_MODE_SLAVE 		(uint8_t)(0)
#define SPI_DEVICE_MODE_MASTER 		(uint8_t)(1<<4)

//@ref SPI_FRAME_FORMAT
#define SPI_FRAME_FORMAT_MSB_transmmitted_first		(uint8_t)(0)
#define SPI_FRAME_FORMAT_LSB_transmmitted_first		(uint8_t)(1<<5)

//@ref SPI_CLKPolarity
#define SPI_CLKPolarity_LEAD_RISING			(uint8_t)(0)
#define SPI_CLKPolarity_LEAD_FALLING		(uint8_t)(1<<3)


// @ref SPI_CLKPhase
#define SPI_Clock_Phase_SAMPLE_FIRST	(uint8_t)(0)
#define SPI_Clock_Phase_SAMPLE_SECOND	(uint8_t)(1<<2)

//@ref SPI_BaudRate

#define SPI_BAUDRATEPRESCALER_2      (uint8_t)(0)
#define SPI_BAUDRATEPRESCALER_4      (uint8_t)(0)
#define SPI_BAUDRATEPRESCALER_8      (uint8_t)(1)
#define SPI_BAUDRATEPRESCALER_16     (uint8_t)(1)
#define SPI_BAUDRATEPRESCALER_32     (uint8_t)(2)
#define SPI_BAUDRATEPRESCALER_64     (uint8_t)(3)
#define SPI_BAUDRATEPRESCALER_128    (uint8_t)(3)


//@ SPI_DOUBLE_SPEED
#define SPI_DOUBLE_ENABLE				(uint8_t)(1)
#define SPI_DOUBLE_DISABLE				(uint8_t)(0)

// @ref SPI_IRQ_Enable
#define SPI_ENABLE_IRQ				(uint8_t)(1<<7)
#define SPI_DISABLE_IRQ				(uint8_t)(0)


typedef enum{
	Pollingenable,
	Pollingdisable
}SPI_Polling_Mechanism;

void MCAL_SPI_Init(SPI_TypeDef* SPIx , SPI_Config* SPI_Config);
void MCAL_SPI_Denit(SPI_TypeDef* SPIx);

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx);

void MCAL_SPI_SendData(SPI_TypeDef* SPIx , uint8_t * pTxBuffer);

void MCAL_SPI_ReceiveData(SPI_TypeDef* SPIx , uint8_t * pTxBuffer);


void MCAL_SPI_TX_RX_UPDATED(SPI_TypeDef* SPIx , uint8_t * pTxBuffer1 , uint8_t * pTxBuffer2);

#endif /* SPI_H_ */