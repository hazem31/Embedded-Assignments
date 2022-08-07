#include "Atmega32.h"
#include "usart.h"


//call back fuctions array
void Default_IRQ_UART_F(void)
{
	
}

IRQ_Cfg Global_I_CallBack = Default_IRQ_UART;

void MCAL_USART_Init(USART_Config * UsartCfg)
{
	
	
	// disable transmition first
	USART->UCSRB_r &= ~(0b11<<TXEN_p);
	
	Interupt_Disable();
	// setting the 12 bit UBRR value for baud rate
	USART->UBRRL_r = (UsartCfg->BAUD_RATE_UBRR & 0xFF);
	Clear_bit(USART->UCSRC_UBRRH,URSEL_p); // write to UBRRH
	USART->UBRRL_r &= ~(0x0F);
	USART->UBRRL_r |= (0x0F & (UsartCfg->BAUD_RATE_UBRR>>8)); 
	
	// mode of operation 
	if (UsartCfg->Mode_Operation == USART_MODE_Normal_Asynchronous || UsartCfg->Mode_Operation == USART_MODE_Double_Asynchronous )
	{
		// select asynch
		Set_bit(USART->UCSRC_UBRRH,URSEL_p); // write to UCSRC	
		Clear_bit(USART->UCSRC_UBRRH,UCPOL_p); // clear sample and output edge
		
		Clear_bit(USART->UCSRC_UBRRH,UMSEL_p);	//select Asynch
		
		// normal or double
		Clear_bit(USART->UCSRA_r,U2X_p); // clear first U2X
		USART->UCSRA_r |= (UsartCfg->Mode_Operation<<U2X_p); // choose normal or double 
		  
	}
	else
	{
		Clear_bit(USART->UCSRA_r,U2X_p);     // clear U2X
		Set_bit(USART->UCSRC_UBRRH,URSEL_p); // write to UCSRC
		Set_bit(USART->UCSRC_UBRRH,UMSEL_p); //select synch
		
		// select direction of clock output is master and input is slave
		Clear_bit(XCK_GPIO_PORT->DDR,XCK_PIN);
		XCK_GPIO_PORT->DDR |= ((UsartCfg->Mode_Operation & 0x1)<<XCK_PIN) ;
		
		//select edge sample mode
		Set_bit(USART->UCSRC_UBRRH,URSEL_p); // write to UCSRC
		USART->UCSRC_UBRRH |= (UsartCfg->EDGE_FOR_SAMPLE_MODE<<UCPOL_p); 
	}
	// frame setup	
	
	// select num of data bits
	// clear bits first
	Clear_bit(USART->UCSRB_r,UCSZ2_p); // clear ucsz2
	Set_bit(USART->UCSRC_UBRRH,URSEL_p); // write to UCSRC
	USART->UCSRC_UBRRH &= ~(0b11<<UCSZ0_p);
	// set the value
	USART->UCSRC_UBRRH |= ((UsartCfg->Data_bits & 0b11)<<UCSZ0_p); // for UCSZ0:1
	USART->UCSRB_r |= ((UsartCfg->Data_bits>>2)<<UCSZ2_p); // for UCSZ2
	
	// parity 
	Set_bit(USART->UCSRC_UBRRH,URSEL_p); // write to UCSRC
	USART->UCSRC_UBRRH &= ~(0b11<<UPM0_p);
	USART->UCSRC_UBRRH |= (UsartCfg->Parity_Mode<<UPM0_p);
	
	// stop bit
	Set_bit(USART->UCSRC_UBRRH,URSEL_p); // write to UCSRC
	USART->UCSRC_UBRRH &= ~(1<<USBS_p);  // clear stop bit
	USART->UCSRC_UBRRH |= (UsartCfg->Stop_bit<<USBS_p);
	
	// intereupts part
	if (UsartCfg->IRQ_CallBack.P_IRQ_CallBack_RXC != Default_IRQ_UART_F)
	{
		Global_I_CallBack.P_IRQ_CallBack_RXC = UsartCfg->IRQ_CallBack.P_IRQ_CallBack_RXC;
		USART->UCSRB_r |= (RXCIE_EN);
	}
	
	if (UsartCfg->IRQ_CallBack.P_IRQ_CallBack_TXC != Default_IRQ_UART_F)
	{
		Global_I_CallBack.P_IRQ_CallBack_TXC = UsartCfg->IRQ_CallBack.P_IRQ_CallBack_TXC;
		USART->UCSRB_r |= (TXCIE_EN);
	}
	
	if (UsartCfg->IRQ_CallBack.P_IRQ_CallBack_UDRE != Default_IRQ_UART_F)
	{
		Global_I_CallBack.P_IRQ_CallBack_UDRE = UsartCfg->IRQ_CallBack.P_IRQ_CallBack_UDRE;
		USART->UCSRB_r |= (UDRIE_EN);
	}
	
	// enable part
	USART->UCSRB_r |= (UsartCfg->TX_RX_ENABLE<<TXEN_p);


	
}

void MCAL_USART_DISABLE(uint8_t Mode)
{
	USART->UCSRB_r &= ~(Mode<<TXEN_p);
}


void MCAL_USART_ENABLE(uint8_t Mode) //@ ref Enable
{
	USART->UCSRB_r |= (Mode<<TXEN_p);
}


uint8_t MCAL_USART_UDRE_FLAG(void)
{
	return Read_bit(USART->UCSRA_r,UDRE_p);
}

uint8_t MCAL_USART_RXC_FLAG(void)
{
	return Read_bit(USART->UCSRA_r,RXC_p);
}

uint8_t MCAL_USART_TXC_FLAG(void)
{
	return Read_bit(USART->UCSRA_r,TXC_p);
}

uint8_t MCAL_USART_FE_FLAG(void)
{
	return Read_bit(USART->UCSRA_r,FE_P);
}

uint8_t MCAL_USART_PE_FLAG(void)
{
	return Read_bit(USART->UCSRA_r,PE_p);
}

uint8_t MCAL_USART_DOR_FLAG(void)
{
	return Read_bit(USART->UCSRA_r,DOR_p);
}


void MCAL_USART_Send(uint16_t * pTxBuffer , enum Polling_Mechanism PollingEn )
{
	uint8_t data2;
	if (PollingEn == enable)
		while(!MCAL_USART_UDRE_FLAG());
	
	if (Read_bit(USART->UCSRB_r,UCSZ2_p))
	{
		data2 = (uint8_t)((*pTxBuffer>>8) & 0x1) ;
		USART->UCSRB_r |= (data2<<TXB8_p);
		USART->UDR_r = (uint8_t)(*pTxBuffer & 0xFF);
	}
	else
	{
		USART->UDR_r = (uint8_t)(*pTxBuffer & 0xFF);
	}
}

void MCAL_USART_Receive(uint16_t * pTxBuffer , enum Polling_Mechanism PollingEn)
{
	
	uint16_t data2;
	if (PollingEn == enable)
		while(!MCAL_USART_RXC_FLAG());
	
	if (Read_bit(USART->UCSRB_r,UCSZ2_p))
	{
		data2 = (uint16_t)(Read_bit(USART->UCSRB_r,RXB8_p));
		*pTxBuffer = ((uint16_t)USART->UDR_r | (data2<<8));
	}
	else
	{
		*pTxBuffer = ((uint16_t)USART->UDR_r);
	}
	
}

ISR (USART_RXC_vect)
{
	Global_I_CallBack.P_IRQ_CallBack_RXC();
}

ISR (USART_UDRE_vect)
{
	Global_I_CallBack.P_IRQ_CallBack_UDRE();
}

ISR (USART_TXC_vect)
{
	Global_I_CallBack.P_IRQ_CallBack_TXC();
}