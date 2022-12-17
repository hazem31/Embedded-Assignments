
#ifndef USART_H_
#define USART_H_

#include "stm32f103x6.h"
#include "rcc.h"
#include "Stm32_F103C6_gpio_driver.h"


#define USARTDIV(_PCLK_,_BAUD_)						((uint32_t)(_PCLK_/(16 * _BAUD_)))
#define USARTDIV_MULL100(_PCLK_,_BAUD_)				((uint32_t)(25 * _PCLK_/(4 * _BAUD_)))
#define Mantissa_MULL100(_PCLK_,_BAUD_)				((uint32_t) USARTDIV( _PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_,_BAUD_)						((uint32_t) USARTDIV( _PCLK_, _BAUD_))
#define DIV_Fraction(_PCLK_,_BAUD_)					((uint32_t) ( ( (USARTDIV_MULL100(_PCLK_,_BAUD_) - Mantissa_MULL100(_PCLK_,_BAUD_)) * 16) / 100))
#define UART_BRR_Register(_PCLK_,_BAUD_)			( (Mantissa(_PCLK_,_BAUD_) << 4) | (DIV_Fraction(_PCLK_,_BAUD_) & 0xF) )


enum USART_IRQ_Event
{
	USART_IRQ_TXE,	//transmit data register empty
	USART_IRQ_TC,	//Transmission complete
	USART_IRQ_RXNE,	//received data ready to be read
	USART_IRQ_ORE,	//overrun error detected
	USART_IRQ_PE     //Parity error
};



enum Polling_Mechanism{
	enable,
	disable
};

typedef struct
{
	void (*P_IRQ_CallBack_TXE)(void);
	void (*P_IRQ_CallBack_TC)(void);
	void (*P_IRQ_CallBack_RXNE)(void);
	void (*P_IRQ_CallBack_PE)(void);
}IRQ_Cfg;

#define Default_IRQ_Cfg		(IRQ_Cfg){NULL,NULL,NULL,NULL}

typedef struct
{
	uint8_t 		USART_Mode; // Enable TX/RX , @ref UART_Mode_define

	uint32_t		BaudRate; //@ref UART_BaudRate define

	uint8_t 		Payload_Length;  // specifies payload length @ref Payload_length

	uint8_t			Parity;	//@ref Parity_define

	uint8_t 		StopBits;	//select number of Stop Bits
								//@ref StopBits_define
	uint8_t HWFlowCTRL;					//enable or disable HW flow control modes
										//@ref HWFlowCTRL_define

	uint8_t IRQ_Enable;				    //enable or disable USART IRQ TX/RX
											//@ref IRQ_Enable_define

	//void (*P_IRQ_CallBack)(void);
	IRQ_Cfg IRQ_CallBack;

}UART_Config;

//=================================================
//=====================Refrence Macros ============
//================================================

//@ref UART_Mode_define
#define UART_Mode_RX		(uint32_t)(1<<2); //Bit 2 TE: Transmitter enable
#define UART_Mode_TX		(uint32_t)(1<<3); //Bit 3 TE: Transmitter enable
#define UART_Mode_TX_RX		(uint32_t)(1<<3 | (1<<2)); //Bit 3:2 TE & RE: enable

//@ref UART_BaudRate define

#define USART_BaudRate_2400				2400
#define USART_BaudRate_9600				9600
#define USART_BaudRate_19200			19200
#define USART_BaudRate_57600			57600
#define USART_BaudRate_115200			115200
#define USART_BaudRate_230400			230400
#define USART_BaudRate_460800			460800
#define USART_BaudRate_921600			921600
#define USART_BaudRate_2250000			2250000
#define USART_BaudRate_4500000			4500000

// specifies payload length @ref Payload_length
#define UART_Payload_Length_8B		(uint32_t)(0) //Bit 12 M: Word length
#define UART_Payload_Length_9B		(uint32_t)(1<<12)

//@ref Parity_define
#define UART_Parity_NONE			(uint32_t)(0)
#define UART_Parity_EVEN			(uint32_t)(1<<10)
#define UART_Parity_ODD				(uint32_t)(1<<9 | 1<<10)

//@ref StopBits_define
#define UART_StopBits__half		(uint32_t)(1<<12)
#define UART_StopBits__1			(uint32_t)(0)
#define UART_StopBits__1_half		(uint32_t)(3<<12)
#define UART_StopBits__2			(uint32_t)(2<<12)

//@ref HWFlowCTRL_define
#define UART_HWFlowCTRL_NONE		(uint32_t)(0)
#define UART_HWFlowCTRL_CTS			(uint32_t)(1<<8)
#define UART_HWFlowCTRL_RTS			(uint32_t)(1<<9)
#define UART_HWFlowCTRL_RTS_CTS		(uint32_t)(1<<8 | 1<<9)


//@ref IRQ_Enable_define
#define  USART_IRQ_Enable			(uint32_t) (1)
#define  USART_IRQ_Disable			(uint32_t) (0)


#define  USART_IRQ_Enable_TXE			(uint32_t) (1<<7)
#define  USART_IRQ_Enable_TC			(uint32_t) (1<<6)
#define  USART_IRQ_Enable_RXNE			(uint32_t) (1<<5)
#define  USART_IRQ_Enable_PE			(uint32_t) (1<<8)


//=================================================
//=====================API =======================
//================================================

void MCAL_UART_Init(USART_TypeDef * USARTx, UART_Config *UART_Config);
void MCAL_UART_DeInit(USART_TypeDef * USARTx);

void MCAL_UART_GPIO_Set_Pins(USART_TypeDef * USARTx);

void MCAL_UART_SendData(USART_TypeDef * USARTx , uint16_t * pTxBuffer , enum Polling_Mechanism PollingEn );
void MCAL_UART_RecieveData(USART_TypeDef * USARTx , uint16_t * pTxBuffer , enum Polling_Mechanism PollingEn );

void MCAL_UART_WAIT_TC(USART_TypeDef * USARTx);



#endif
