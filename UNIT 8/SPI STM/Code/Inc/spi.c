/*
 * spi.c
 *
 *  Created on: ١٥‏/١١‏/٢٠٢٢
 *      Author: hazem
 */


#include "spi.h"


/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */

SPI_Config* Global_SPI_Config[2] = {NULL , NULL};


 /*
  * =======================================================================================
  * 							Generic Macros
  * =======================================================================================
  */

#define   SPI1_Index      0
#define   SPI2_Index      1


#define   SPI_SR_RXNE            ((uint8_t)0x01)         //Bit 0 RXNE: Receive buffer not empty
#define   SPI_SR_TX              ((uint8_t)0x02)         //Bit 1 TXE: Transmit buffer empty


/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */



/*
 * ========================================================================
 *                            APIs Function Definitions
 * ========================================================================
 */

/**================================================================
 * @Fn				- MCAL_SPI_Init
 * @brief 			- Initialize the SPI according to the specified parameter
 * @param [in] 		- SPIx : where x can be (1,2 depending on device used)
 * @param [in] 		- SPI_Config : All UART Configuration EXTI_PinConfig_t
 * @retval 			- None
 * Note				- Support for SPI Full Duplex Master/Slave only & NSS HW/SW
 * 					- in case of master you have to configure pin and drive it
 */
void MCAL_SPI_Init(SPI_TypeDef* SPIx , SPI_Config* SPI_Config)
{
	uint16_t tempreg_CR1 = 0;
	uint16_t tempreg_CR2 = 0;

	if(SPIx == SPI1)
	{
		Global_SPI_Config[SPI1_Index] = SPI_Config;
		RCC_SPI1_CLK_EN();
	}
	else
	{
		Global_SPI_Config[SPI2_Index] = SPI_Config;
		RCC_SPI2_CLK_EN();
	}

	// Enable SPI CR1 -> Bit6 SPE: SPI enable
	tempreg_CR1 = (1<<6);

	// Master or Slave
	tempreg_CR1 |= SPI_Config->Device_Mode;

	// SPI_communication_Mode
	tempreg_CR1 |= SPI_Config->Communicaion_Mode;

	// SPI_Frame_Format
	tempreg_CR1 |= SPI_Config->Frame_Format;

	// SPI_DataSize
	tempreg_CR1 |= SPI_Config->Data_Size;

	// SPI_Clock_Polarity
	tempreg_CR1 |= SPI_Config->CLKPolarity;

	// SPI_Clock_Phase
	tempreg_CR1 |= SPI_Config->CLKPhase;


	if(SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_enable)
	{
		tempreg_CR2 |= SPI_Config->NSS;

	}else if(SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_enable)
	{
		tempreg_CR2 &= SPI_Config->NSS;
	}
	else
	{
		// rest in CR1
		tempreg_CR1 |= SPI_Config->NSS;
	}


	tempreg_CR1 |= SPI_Config->SPI_BAUDRATEPRESCALER;


	if(SPI_Config->IRQ_Enable.ENABLE != SPI_DISABLE_IRQ)
	{
		if(SPI_Config->IRQ_Enable.TXE) {tempreg_CR2 |= SPI_IRQ_Enable_TXEIE;}
		if(SPI_Config->IRQ_Enable.RXNE) {tempreg_CR2 |= SPI_IRQ_Enable_RXNEIE;}
		if(SPI_Config->IRQ_Enable.ERRiI) {tempreg_CR2 |= SPI_IRQ_Enable_ERRIE;}
		//tempreg_CR2 |= SPI_Config->IRQ_Enable;
		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable();
		}
		else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Enable();
		}
	}

	SPIx->SPI_CR1 = tempreg_CR1;
	SPIx->SPI_CR2 = tempreg_CR2;

}

/**================================================================
 * @Fn				- MCAL_SPI_DeInit
 * @brief 			- DeInitialize all SPI registers
 * @param [in] 		- SPIx : where x can be (1,2 depending on device used)
 * @retval 			- None
 * Note				- None
 */

void MCAL_SPI_DeInit(SPI_TypeDef* SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable();
		RCC_SPI1_Reset();
	}
	else if(SPIx == SPI2)
	{
			NVIC_IRQ36_SPI2_Disable();
			RCC_SPI2_Reset();
	}
}


/**================================================================
 * @Fn				- MCALSPI_Send_Data
 * @brief 			- transmit Buffer on SPI
 * @param [in] 		- SPIx : where x can be (1,2 depending on device used)
 * @param [in] 		- Buffer : Buffer for data will be send
 * @param [in]		- PollingEn : Enable pooling or disable it
 * @retval 			- None
 * Note				- None
 */

void MCAL_SPI_SendData(SPI_TypeDef* SPIx , uint16_t * pTxBuffer , SPI_Polling_Mechanism PollingEn)
{
	if(PollingEn == Pollingenable)
		while(!(SPIx->SPI_SR & SPI_SR_TX));

	SPIx->SPI_DR = *pTxBuffer;
}


/**================================================================
 * @Fn				- MCAL_SPI_Recieve_Data
 * @brief 			- Receive Buffer from SPI
 * @param [in] 		- SPIx : where x can be (1,2 depending on device used)
 * @param [in] 		- Buffer : Buffer for data will be received
 * @param [in]		- PollingEn : Enable pooling or disable it
 * @retval 			- None
 * Note				- None
 */

void MCAL_SPI_ReceiveData(SPI_TypeDef* SPIx , uint16_t * pTxBuffer , SPI_Polling_Mechanism PollingEn)
{
	if(PollingEn == Pollingenable)
		while(!(SPIx->SPI_SR & SPI_SR_RXNE));

	*pTxBuffer = SPIx->SPI_DR;
}

/**================================================================
 * @Fn				- MCAL_SPI_RX_TX
 * @brief 			- Transmit and Receive Buffer on SPI at the same time
 * @param [in] 		- SPIx : where x can be (1,2 depending on device used)
 * @param [in] 		- Buffer : Buffer for data will be transmitted and received
 * @param [in]		- PollingEn : Enable pooling or disable it
 * @retval 			- None
 * Note				- None
 */

void MCAL_SPI_TX_RX(SPI_TypeDef* SPIx , uint16_t * pTxBuffer , SPI_Polling_Mechanism PollingEn)
{
	if(PollingEn == Pollingenable)
		while(!(SPIx->SPI_SR & SPI_SR_TX));

	SPIx->SPI_DR = *pTxBuffer;

	if(PollingEn == Pollingenable)
		while(!(SPIx->SPI_SR & SPI_SR_RXNE));

	*pTxBuffer = SPIx->SPI_DR;


}


/**================================================================
 * @Fn				- MCAL_SPI_GPIO_Set_Pins
 * @brief 			- Configure SPI pins
 * @param [in] 		- SPIx : where x can be (1,2 depending on device used)
 * @retval 			- None
 * Note				- None
 */
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx)
{
	GPIO_PinConfig_t PinCfg;
	if(SPIx == SPI1)
	{
		// From STM32F103xx pin definitions table
				//   	PA4 : SPI1_NSS
				//   	PA5 : SPI1_SCK
				//		PA6 : SPI1_MISO
				//   	PA7 : SPI1_MOSI
		// master setup
		if(Global_SPI_Config[SPI1_Index]->Device_Mode == SPI_DEVICE_MODE_MASTER)
		{

			// nss PA4
			switch(Global_SPI_Config[SPI1_Index]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_disable:

				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;

			case SPI_NSS_Hard_Master_SS_output_enable:

				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;
			}

			//PA5 clk
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			// only full dublex
			//PA6 MISO in master input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			// PA7 MOSI in master output
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);



		}else // slave
		{

			//PA4 nss
			if(Global_SPI_Config[SPI1_Index]->NSS == SPI_NSS_Hard_Slave)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}

			//PA5 clk slave in
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			// PA6 miso slave output
			PinCfg.GPIO_PinNumber = GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA7 MOSI slave input
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}
	}
	else if(SPIx == SPI2)
	{
		// From STM32F103xx pin definitions table
				//   	PB12 : SPI2_NSS
				//   	PB13 : SPI2_SCK
				//   	PB14 : SPI2_MISO
				//   	PB15 : SPI2_MOSI
		if(Global_SPI_Config[SPI2_Index]->Device_Mode == SPI_DEVICE_MODE_MASTER)
		{

			// nss PB12
			switch(Global_SPI_Config[SPI2_Index]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_disable:

				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break;

			case SPI_NSS_Hard_Master_SS_output_enable:

				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break;
			}

			//PB13 clk
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			// only full dublex
			//PB14 MISO in master input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			// PB15 MOSI in master output
			PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);



		}else // slave
		{

			//PB12 nss
			if(Global_SPI_Config[SPI1_Index]->NSS == SPI_NSS_Hard_Slave)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}

			//PB13 clk slave in
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			// PB14 miso slave output
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB15 MOSI slave input
			PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

		}

	}
}

/*
 * =================================================================
 *                            IRQ
 * =================================================================
 */


void SPI1_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src;

	irq_src.TXE = ((SPI1->SPI_SR & (1<<1)) >> 1);
	irq_src.RXNE = ((SPI1->SPI_SR & (1<<0)) >> 0);
	irq_src.ERRiI = ((SPI1->SPI_SR & (1<<4)) >> 4);

	Global_SPI_Config[SPI1_Index]->P_IRQ_callBack(irq_src);
}


void SPI2_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src;

	irq_src.TXE = ((SPI2->SPI_SR & (1<<1)) >> 1);
	irq_src.RXNE = ((SPI2->SPI_SR & (1<<0)) >> 0);
	irq_src.ERRiI = ((SPI2->SPI_SR & (1<<4)) >> 4);

	Global_SPI_Config[SPI2_Index]->P_IRQ_callBack(irq_src);
}
