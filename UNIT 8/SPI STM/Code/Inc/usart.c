

#include "usart.h"


/*
 * =========================================================================
 * 							Generic Variables
 * ==========================================================================
 */


UART_Config * Global_UART_Config = NULL;

// we have 3 uart then 3 call_back functions , but
// note here that each uart must have a number of callbacks not one due to diff interupts (TXE,RXE ) etc
// you can make a another struct in cfg struct containing pointers to variables to all possible interupts
// and each pointer related to IRQ function from that , and if it NULL then we don;t won't to set that driver
// instead off IRQ ENable and pointer to function
IRQ_Cfg Global_I_UART[3] = {Default_IRQ_Cfg,Default_IRQ_Cfg,Default_IRQ_Cfg};
/*
 * =========================================================================
 * 							Generic Macros
 * ==========================================================================
 */


/*
 * =========================================================================
 * 							Generic Functions
 * ==========================================================================
 */


/*
 * =========================================================================
 * 							API'S Functions Definitions
 * ==========================================================================
 */


/**================================================================
* @Fn					- MCAL_UART_Init
* @brief 				- initialize USARTx Registers  correspondin UART_cnfg
* @param [in] 			- USARTx : where x can be (1,2,3,.. depending on device used)
* @param [in] 			- UART_cnfg : UART configuration Specified by the user
* @retval 				- none
* Note					- Now Support ASYNCH mode and Clock 8Mhz
*/
/**================================================================*/

void MCAL_UART_Init(USART_TypeDef * USARTx, UART_Config *UART_Config)
{
	uint32_t pclK , BRR;
	Global_UART_Config = UART_Config;

	if(USARTx == USART1)
	{
		RCC_USART1_CLK_EN();
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_CLK_EN();
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLK_EN();
	}
	//Enable USART Module
	//	USART_CR1  Bit 13 UE: USART enable
	USARTx->CR1 |= 1<<13;

	//Enable TX and RX
	//Bit 3 TE: Transmitter enable
	//Bit 2 RE: Receiver enable
	USARTx-> CR1 |= UART_Config->USART_Mode;
	//PAYLOAD Width
	USARTx->CR1 |= UART_Config->Payload_Length;

	//Configuration of Parity control bit
	USARTx->CR1 |= UART_Config->Parity;

	//Configure the number of stop bits
	USARTx->CR2 |= UART_Config->StopBits;

	//USART hardware flowControl
	USARTx->CR3 |= UART_Config->HWFlowCTRL;

	if(USARTx == USART1)
	{
		pclK = MCAL_RCC_GetPCLK2Freq();
	}
	else
	{
		pclK = MCAL_RCC_GetPCLK1Freq();
	}

	BRR = UART_BRR_Register(pclK, UART_Config->BaudRate);
	USARTx->BRR = BRR;

	if(UART_Config->IRQ_Enable != USART_IRQ_Disable)
	{
		if(UART_Config->IRQ_CallBack.P_IRQ_CallBack_TC != NULL)
			USARTx->CR1 |=  (USART_IRQ_Enable_TC);

		if(UART_Config->IRQ_CallBack.P_IRQ_CallBack_TXE != NULL)
				USARTx->CR1 |=  (USART_IRQ_Enable_TXE);

		if(UART_Config->IRQ_CallBack.P_IRQ_CallBack_PE != NULL)
				USARTx->CR1 |=  (USART_IRQ_Enable_PE);

		if(UART_Config->IRQ_CallBack.P_IRQ_CallBack_RXNE != NULL)
				USARTx->CR1 |=  (USART_IRQ_Enable_RXNE);


		if(USARTx == USART1)
		{
			NVIC_IRQ37_USART1_Enable();
			Global_I_UART[0] = UART_Config->IRQ_CallBack;
		}
		else if(USARTx == USART2)
		{
			NVIC_IRQ38_USART2_Enable();
			Global_I_UART[1] = UART_Config->IRQ_CallBack;
		}
		else if(USARTx == USART3)
		{
			NVIC_IRQ39_USART3_Enable();
			Global_I_UART[2] = UART_Config->IRQ_CallBack;
		}
	}
}


/**================================================================
* @Fn					- MCAL_UART_DeInit
* @brief 				- deinitialize USARTx Registers
* @param [in] 			- USARTx : where x can be (1,2,3,.. depending on device used)
* @retval 				- none
* Note					- Now Support ASYNCH mode and Clock 8Mhz
*/
/**================================================================*/

void MCAL_UART_DeInit(USART_TypeDef * USARTx)
{
		if(USARTx == USART1)
		{
			RCC_USART1_Reset();
			NVIC_IRQ37_USART1_Disable();
		}
		else if(USARTx == USART2)
		{
			RCC_USART2_Reset();
			NVIC_IRQ38_USART2_Disable();
		}
		else if(USARTx == USART3)
		{
			RCC_USART3_Reset();
			NVIC_IRQ39_USART3_Disable();
		}
}

void MCAL_UART_GPIO_Set_Pins(USART_TypeDef * USARTx)
{
	GPIO_PinConfig_t PinCfg;

	if(USARTx == USART1)
	{
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if(Global_UART_Config->HWFlowCTRL == UART_HWFlowCTRL_CTS || Global_UART_Config->HWFlowCTRL == UART_HWFlowCTRL_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_11;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
		if(Global_UART_Config->HWFlowCTRL == UART_HWFlowCTRL_RTS || Global_UART_Config->HWFlowCTRL == UART_HWFlowCTRL_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

	}
	else if(USARTx == USART2)
	{
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		PinCfg.GPIO_PinNumber = GPIO_PIN_2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		PinCfg.GPIO_PinNumber = GPIO_PIN_3;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if(Global_UART_Config->HWFlowCTRL == UART_HWFlowCTRL_CTS || Global_UART_Config->HWFlowCTRL == UART_HWFlowCTRL_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
		if(Global_UART_Config->HWFlowCTRL == UART_HWFlowCTRL_RTS || Global_UART_Config->HWFlowCTRL == UART_HWFlowCTRL_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_1;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

	}
	else if(USARTx == USART3)
	{
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		if(Global_UART_Config->HWFlowCTRL == UART_HWFlowCTRL_CTS || Global_UART_Config->HWFlowCTRL == UART_HWFlowCTRL_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
		if(Global_UART_Config->HWFlowCTRL == UART_HWFlowCTRL_RTS || Global_UART_Config->HWFlowCTRL == UART_HWFlowCTRL_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}

	}

}


/**================================================================
* @Fn					- MCAL_UART_SendData
* @brief 				- initialize USARTx Registers  correspondin UART_cnfg
* @param [in] 			- USARTx : where x can be (1,2,3,.. depending on device used)
* @param [in] 			- pTxBuffer
* @param [in] 			- PollingEn : Enable polling or disabling it
* @retval 				- none
* Note					- shoud initialize UART first
* 						When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
							//the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
							//because it is replaced by the parity.
							//When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.
*/
/**================================================================*/

void MCAL_UART_SendData(USART_TypeDef * USARTx , uint16_t * pTxBuffer , enum Polling_Mechanism PollingEn )
{
	//wait TXE is set
	if(PollingEn == enable)
		while(! (USARTx->SR & (1<<7) ));

//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
//	because it is replaced by the parity.
//	When receiving with the parity enabled, the value read in the MSB bit is the received parity
//	bit. , so what happens when you write the bits it auto caluculates parity and put it in DR then send it

	//check usart wordlength item for 9 bit or 8 bit
	if(Global_UART_Config->Payload_Length == UART_Payload_Length_9B)
	{
		USARTx->DR = ((*pTxBuffer) & (uint16_t)0x1FF);
	}
	else
	{
		USARTx->DR = ((*pTxBuffer) & (uint16_t)0x0FF);
	}
}

void MCAL_UART_RecieveData(USART_TypeDef * USARTx , uint16_t * pTxBuffer , enum Polling_Mechanism PollingEn )
{
	if(PollingEn == enable)
		while(!(USARTx->SR & 1<<5));

	if(Global_UART_Config->Payload_Length == UART_Payload_Length_9B)
	{
		if(Global_UART_Config->Parity == UART_Parity_NONE)
		{
			//no parity so all 9bits are considered data
			*pTxBuffer = ((uint16_t)USARTx->DR & (uint16_t)0x1FF ) ;
		}
		else
		{
			//parity is used so 8 bit will be of user data and 1 for parity
			*pTxBuffer = ((uint16_t)USARTx->DR & (uint16_t)0xFF);
		}
	}
	else
	{
		if(Global_UART_Config->Parity == UART_Parity_NONE)
		{

			*pTxBuffer = ((uint16_t)USARTx->DR & (uint16_t)0xFF);
		}
		else
		{
			*pTxBuffer = ((uint16_t)USARTx->DR & (uint16_t)0x7F);
		}

	}


}
void MCAL_UART_TC(USART_TypeDef * USARTx)
{
	while(!(USARTx->SR & (1<<6)));
}


void USART1_IRQHandler(void)
{
	if(USART1->SR & (1<<6)) { if(Global_I_UART[0].P_IRQ_CallBack_TC != NULL)   Global_I_UART[0].P_IRQ_CallBack_TC(); }
	if(USART1->SR & (1<<5)) { if(Global_I_UART[0].P_IRQ_CallBack_RXNE != NULL) Global_I_UART[0].P_IRQ_CallBack_RXNE(); }
	if(USART1->SR & (1<<7)) { if(Global_I_UART[0].P_IRQ_CallBack_TXE != NULL)  Global_I_UART[0].P_IRQ_CallBack_TXE(); }
	if(USART1->SR & (1<<0)) { if(Global_I_UART[0].P_IRQ_CallBack_PE != NULL)   Global_I_UART[0].P_IRQ_CallBack_PE(); }
}

void USART2_IRQHandler(void)
{
	if(USART2->SR & (1<<6)) { if(Global_I_UART[1].P_IRQ_CallBack_TC != NULL)   Global_I_UART[1].P_IRQ_CallBack_TC(); }
	if(USART2->SR & (1<<5)) { if(Global_I_UART[1].P_IRQ_CallBack_RXNE != NULL) Global_I_UART[1].P_IRQ_CallBack_RXNE(); }
	if(USART2->SR & (1<<7)) { if(Global_I_UART[1].P_IRQ_CallBack_TXE != NULL)  Global_I_UART[1].P_IRQ_CallBack_TXE(); }
	if(USART2->SR & (1<<0)) {  if(Global_I_UART[1].P_IRQ_CallBack_TXE != NULL) Global_I_UART[1].P_IRQ_CallBack_PE(); }
}


void USART3_IRQHandler(void)
{
	if(USART3->SR & (1<<6)) { if(Global_I_UART[2].P_IRQ_CallBack_TC != NULL) Global_I_UART[2].P_IRQ_CallBack_TC(); }
	if(USART3->SR & (1<<5)) {  if(Global_I_UART[2].P_IRQ_CallBack_RXNE != NULL) Global_I_UART[2].P_IRQ_CallBack_RXNE(); }
	if(USART3->SR & (1<<7)) { if(Global_I_UART[2].P_IRQ_CallBack_TXE != NULL)  Global_I_UART[2].P_IRQ_CallBack_TXE(); }
	if(USART3->SR & (1<<0)) {  if(Global_I_UART[2].P_IRQ_CallBack_TXE != NULL) Global_I_UART[2].P_IRQ_CallBack_PE(); }
}
