/*
 * usart.h
 *
 * Created: 17/06/2022 05:50:13 م
 *  Author: hazem
 */ 


#ifndef USART_H_
#define USART_H_

#include "Atmega32.h"
#include "gpio.h"

//pins

void Default_IRQ_UART_F(void);

#define TX_RX_GPIO_PORT			GPIOD
#define RX_PIN					GPIO_PIN_0
#define TX_PIN					GPIO_PIN_1
#define XCK_GPIO_PORT			GPIOB
#define XCK_PIN					GPIO_PIN_0

#define UMSEL_p		6	// selects synch or asych 
#define URSEL_p		7   // write to UCSRC or UBRRH
#define U2X_p		1	// normal or double asynch
#define UCPOL_p		0   // Sample Edge
// bits that controls data bits 
#define UCSZ0_p		1 // UCSZ0 
#define UCSZ1_p		2 // UCSZ1
#define UCSZ2_p		2 // UCSZ2

#define UPM0_p		4 // parity
#define UPM1_p		5 // parity
#define USBS_p		3 // stop bit

#define TXEN_p		3
#define RXEN_p		4

#define UDRE_p		5
#define TXC_p		6
#define RXC_p		7

#define FE_P		4
#define DOR_p		3
#define PE_p		2

#define TXB8_p		0
#define RXB8_p		1

#define UDRIE_EN		(uint8_t)(1<<5)
#define TXCIE_EN		(uint8_t)(1<<6)
#define RXCIE_EN		(uint8_t)(1<<7)

enum Polling_Mechanism{
	enable,
	disable
};

typedef struct
{
	void (*P_IRQ_CallBack_RXC)(void);
	void (*P_IRQ_CallBack_UDRE)(void);
	void (*P_IRQ_CallBack_TXC)(void);
}IRQ_Cfg;

#define Default_IRQ_UART	(IRQ_Cfg){Default_IRQ_UART_F,Default_IRQ_UART_F,Default_IRQ_UART_F} 


typedef struct
{
	// clock and mode setup
	uint8_t	 Mode_Operation; // which mode to take of 4 modes , @ref USART_MODE
	uint16_t BAUD_RATE_UBRR; // value in UBBR to determine baud rate
	uint8_t  EDGE_FOR_SAMPLE_MODE; // used with synchronous mode only UCPOL bit  , @ref SAMPLE_EDGE SAMPLE_NEG_OUT_POSTIVE
	// frame setup
	uint8_t Data_bits; //number o data bits in frame from 5 to 9 ,@ref DATA_BITS
	uint8_t Parity_Mode; // @ref Parity mode 
	uint8_t Stop_bit; // number of stop bits , @ref STOP_BIT
	uint8_t TX_RX_ENABLE; // enable transmit or recieve or both, @ref ENBALE
	
	enum Polling_Mechanism PollingEnable; //
	
	IRQ_Cfg IRQ_CallBack;
	
	// interrupt part    
}USART_Config;

//@ref ENABLE
#define ENABLE_TX_RX	0b11
#define ENABLE_TX		0b01
#define ENABLE_RX		0b10

//@ref DISABLE
#define DISABLE_TX_RX	0b11
#define DISABLE_TX		0b01
#define DISABLE_RX		0b10


//@ref STOP_BIT
#define STOP_ONE_BIT 0
#define STOP_TWO_BIT 1
//@ref PAERITY_MODE
#define PARITY_DISABLED		0
#define PARITY_EVEN			2
#define PARITY_ODD			3

//@ref DATA_BITS
#define DATA_BITS_5		0b000
#define DATA_BITS_6		0b001
#define DATA_BITS_7		0b010
#define DATA_BITS_8		0b011
#define DATA_BITS_9		0b111

//@ref SAMPLE_EDGE
#define SAMPLE_NEG_OUT_POS	0
#define SAMPLE_POS_OUT_NEG	1

//@ref USART_MODE
#define USART_MODE_Normal_Asynchronous		0
#define USART_MODE_Double_Asynchronous		1
#define USART_MODE_Slave_Synchronous		2
#define USART_MODE_Master_Synchronous		3

#define URSEL_UBBRH		0 // select UBBRH
#define URSEL_UCSRC		1 // select UBBRH

void MCAL_USART_Init(USART_Config * UsartCfg);

void MCAL_USART_DISABLE(uint8_t Mode); //@ ref Disable
void MCAL_USART_ENABLE(uint8_t Mode); //@ ref Enable

uint8_t MCAL_USART_UDRE_FLAG(void);

uint8_t MCAL_USART_RXC_FLAG(void);

uint8_t MCAL_USART_TXC_FLAG(void);

uint8_t MCAL_USART_FE_FLAG(void);

uint8_t MCAL_USART_DOR_FLAG(void);

uint8_t MCAL_USART_PE_FLAG(void);

void MCAL_USART_Send(uint16_t * pTxBuffer , enum Polling_Mechanism PollingEn );

void MCAL_USART_Receive(uint16_t * pTxBuffer , enum Polling_Mechanism PollingEn);


#endif /* USART_H_ */