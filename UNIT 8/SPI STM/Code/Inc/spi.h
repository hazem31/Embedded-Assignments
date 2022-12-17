/*
 * spi.h
 *
 *  Created on: ١٥‏/١١‏/٢٠٢٢
 *      Author: hazem
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"


struct S_IRQ_SRC
{
	uint8_t TXE:1;
	uint8_t RXNE:1;
	uint8_t ERRiI:1;
	uint8_t Reserved:5;
};

typedef struct{
	uint8_t Reserved:4;
	uint8_t ENABLE:1;
	uint8_t ERRiI:1;
	uint8_t RXNE:1;
	uint8_t TXE:1;

}SPI_IRQ_EN;

typedef struct {

	uint16_t Device_Mode; // SPI operating mode @ref SPI_DEVICE_MODE
	uint16_t Communicaion_Mode; // SPI bidirectional mode state @ref SPI_Communication_MODE
	uint16_t Frame_Format;	// SPI LSB or MSB @ref SPI_FRAME_FORMAT
	uint16_t Data_Size;		//SPI frame length 8 or 16 bir @ref DATA_SIZE
	uint16_t CLKPolarity; // @ref SPI_CLKPolarity
	uint16_t CLKPhase; 	  // @ref SPI_CLKPhase
	uint16_t NSS; 		// Specifies whether the NSS Signal is managed by hardware or by software using SSI and SSM pin @ref SPI_NSS
	uint16_t SPI_BAUDRATEPRESCALER; /* Specifies the Baud rate Prescaler value which will be used to configure the Transmit and receive Clock This parameter is set @ref SPI_BaudRate*/
	SPI_IRQ_EN IRQ_Enable; // This parameter is set @ref SPI_IRQ_Enable

	void(* P_IRQ_callBack)(struct S_IRQ_SRC irq_src);

}SPI_Config;


//=================================================
//=====================Refrence Macros ============
//================================================

//@ref SPI_DEVICE_MODE

#define SPI_DEVICE_MODE_SLAVE 		(uint32_t)(0)
#define SPI_DEVICE_MODE_MASTER 		(uint32_t)(1<<2)


//@ref SPI_Communication_MODE
#define SPI_DIRECTION_2LINES				(uint32_t)(0)
#define SPI_DIRECTION_2LINES_RXONLY			(uint32_t)(1<<10)
#define SPI_DIRECTION_1LINES_receive_only	(uint32_t)(1<<15)
#define SPI_DIRECTION_1LINES_transmit_only	(uint32_t)((1<<15) | (1<<14))

//@ref SPI_FRAME_FORMAT

#define SPI_FRAME_FORMAT_MSB_transmmitted_first		(uint32_t)(0)
#define SPI_FRAME_FORMAT_LSB_transmmitted_first		(uint32_t)(1<<7)

//@ref DATA_SIZE

#define SPI_DataSize_8BIT		(uint32_t)(0)
#define SPI_DataSize_16BIT		(uint32_t)(1<<11)

//@ref SPI_CLKPolarity
#define SPI_CLKPolarity_LOW_when_idle		(uint32_t)(0)
#define SPI_CLKPolarity_HIGH_when_idle		(uint32_t)(1<<1)


// @ref SPI_CLKPhase
#define SPI_Clock_Phase_1EDGE_first_data_capture_edge	(uint32_t)(0)
#define SPI_Clock_Phase_2EDGE_first_data_capture_edge	(uint32_t)(1<<0)

//@ref SPI_NSS

//Hardware
#define SPI_NSS_Hard_Slave 							(uint32_t)(0)
#define SPI_NSS_Hard_Master_SS_output_enable		(uint32_t)(1<<2)
#define SPI_NSS_Hard_Master_SS_output_disable		 ~((uint32_t)(1<<2))

//Software
#define SPI_NSS_Soft_NSSInternalSoft_Reset 			(uint32_t)(1<<9)
#define SPI_NSS_Soft_NSSInternalSoft_Set 			(uint32_t)((1<<9) | (1<<8))

//@ref SPI_BaudRate

#define SPI_BAUDRATEPRESCALER_2      (uint32_t)(0)
#define SPI_BAUDRATEPRESCALER_4      (uint32_t)(1<<3)
#define SPI_BAUDRATEPRESCALER_8      (uint32_t)(2<<3)
#define SPI_BAUDRATEPRESCALER_16     (uint32_t)(3<<3)
#define SPI_BAUDRATEPRESCALER_32     (uint32_t)(4<<3)
#define SPI_BAUDRATEPRESCALER_64     (uint32_t)(5<<3)
#define SPI_BAUDRATEPRESCALER_128    (uint32_t)(6<<3)
#define SPI_BAUDRATEPRESCALER_256    (uint32_t)(7<<3)

// @ref SPI_IRQ_Enable

#define SPI_ENABLE_IRQ				1
#define SPI_DISABLE_IRQ				0

#define SPI_IRQ_Enable_NONE 		(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE		(uint32_t)(1<<7)
#define SPI_IRQ_Enable_RXNEIE		(uint32_t)(1<<6)
#define SPI_IRQ_Enable_ERRIE		(uint32_t)(1<<5)


typedef enum{
	Pollingenable,
	Pollingdisable
}SPI_Polling_Mechanism;



void MCAL_SPI_Init(SPI_TypeDef* SPIx , SPI_Config* SPI_Config);
void MCAL_SPI_Denit(SPI_TypeDef* SPIx);

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx);

void MCAL_SPI_SendData(SPI_TypeDef* SPIx , uint16_t * pTxBuffer , SPI_Polling_Mechanism PollingEn);

void MCAL_SPI_ReceiveData(SPI_TypeDef* SPIx , uint16_t * pTxBuffer ,  SPI_Polling_Mechanism PollingEn);

void MCAL_SPI_TX_RX(SPI_TypeDef* SPIx , uint16_t * pTxBuffer , SPI_Polling_Mechanism PollingEn);

#endif /* SPI_H_ */
