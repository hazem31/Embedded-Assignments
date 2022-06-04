/*
 * EXTI.c
 *
 *  Created on: ١٨‏/٠٥‏/٢٠٢٢
 *      Author: hazem
 */

#include "EXTI.h"
#include "Stm32_F103C6_gpio_driver.h"


//-*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*-
//Generic Variables
//-*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*-


void(* GP_IRQ_callBack[15])(void);



//-*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*-
//Generic Macros
//-*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*-


#define AFIO_GPIO_EXTI_Mapping(x)		((x==GPIOA) ? 0 :\
										(x==GPIOB) ? 1 :\
										(x==GPIOC) ? 2 :\
										(x==GPIOD) ? 3 : 0 )// here GPIOA is default



//-*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*-
//Generic Functions
//-*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*-

void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
			NVIC_IRQ6_EXTI0_Enable();
			break;
	case 1:
			NVIC_IRQ7_EXTI1_Enable();
			break;
	case 2:
			NVIC_IRQ8_EXTI2_Enable();
			break;
	case 3:
			NVIC_IRQ9_EXTI3_Enable();
			break;
	case 4:
			NVIC_IRQ10_EXTI4_Enable();
			break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable();
		break;

	}

}

void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
			NVIC_IRQ6_EXTI0_Disable();
			break;
	case 1:
			NVIC_IRQ7_EXTI1_Disable();
			break;
	case 2:
			NVIC_IRQ8_EXTI2_Disable();
			break;
	case 3:
			NVIC_IRQ9_EXTI3_Disable();
			break;
	case 4:
			NVIC_IRQ10_EXTI4_Disable();
			break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable();
		break;

	}

}


/**================================================================
 * @Fn				-Update_EXTI
 * @brief 			-update the EXTIx Registers and NVIC and IRQ mask
 * @param [in] 	-
 * @param [in] 	-         		 .
 * @retval 		-
 *
 */
void Update_EXTI(EXTI_PinConfig_t * EXTI_Config)
{
	//1- config GPIO as AF input -> floating input
	GPIO_PinConfig_t PinCfg;
	PinCfg.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_PORT, &PinCfg);

	//2- UPDATE AFIO to route between EXTI Line with PORT A,B,C,D

	uint8_t AFIO_EXTICR_index =	EXTI_Config->EXTI_PIN.ETI_InputLineNumber / 4;
	uint8_t AFIO_EXTICR_postion = (EXTI_Config->EXTI_PIN.ETI_InputLineNumber % 4) * 4;


	AFIO->EXTICR[AFIO_EXTICR_index] &= ~(0xF << AFIO_EXTICR_postion);

	AFIO->EXTICR[AFIO_EXTICR_index]	|= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_PORT) & 0x0F) << AFIO_EXTICR_postion);

	// 3 - enable rising or falling edge

	EXTI->RTSR &= ~(1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	EXTI->FTSR &= ~(1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	if(EXTI_Config->Trigger_Case == EXTI_Trigger_RISING)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}
	else if(EXTI_Config->Trigger_Case == EXTI_Trigger_FALLING)
	{
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}
	else if (EXTI_Config->Trigger_Case == EXTI_Trigger_RisingAndFalling)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}

	// 4 - update IRQ Handling callback Function;

	GP_IRQ_callBack[EXTI_Config->EXTI_PIN.ETI_InputLineNumber] = EXTI_Config->P_IRQ_callBack;

	//5- Enable or disable IRQ and NVIC

	if( EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |= (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		Enable_NVIC(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}
	else
	{
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		Disable_NVIC(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}
}

/**================================================================
 * @Fn				-MCAL_EXTI_GPIO_Init
 * @brief 			-init the EXTIx Registers and configure it
 * @param [in] 	-	EXTI_PinConfig_t * EXTI_Config
 * @param [in] 	-         		 .
 * @retval 		-
 *
 */
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t * EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}


/**================================================================
 * @Fn				-MCAL_EXTI_GPIO_DeInit
 * @brief 			-reset the EXTIx Registers and NVIC and IRQ mask
 * @param [in] 	-
 * @param [in] 	-         		 .
 * @retval 		-
 *
 */
void MCAL_EXTI_GPIO_DeInit(void)
{
	EXTI->IMR = 0x00000000;
	EXTI->EMR = 0x00000000;
	EXTI->RTSR = 0x00000000;
	EXTI->FTSR = 0x00000000;
	EXTI->SWIER = 0x00000000;
	// rc_w1
	EXTI->PR = 0xFFFFFFFF;

	// disable EXTI from NVIC
	NVIC_IRQ6_EXTI0_Disable();
	NVIC_IRQ7_EXTI1_Disable();
	NVIC_IRQ8_EXTI2_Disable();
	NVIC_IRQ9_EXTI3_Disable();
	NVIC_IRQ10_EXTI4_Disable();
	NVIC_IRQ23_EXTI5_9_Disable();
	NVIC_IRQ40_EXTI10_15_Disable();

}

/**================================================================
 * @Fn				-MCAL_EXTI_GPIO_Update
 * @brief 			-updates the EXTIx Registers and configure it
 * @param [in] 	-	EXTI_PinConfig_t * EXTI_Config
 * @param [in] 	-         		 .
 * @retval 		-
 *
 */


void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t * EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}


//-*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*-
//ISR Functions
//-*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*--*-*-




void EXTI0_IRQHandler(void)
{
	// clear the bit in the pending register
	EXTI->PR |= (1<<0);
	// call the CallBack Function
	GP_IRQ_callBack[0]();
}


void EXTI1_IRQHandler(void)
{

	EXTI->PR |= (1<<1);
	GP_IRQ_callBack[1]();
}


void EXTI2_IRQHandler(void)
{

	EXTI->PR |= (1<<2);
	GP_IRQ_callBack[2]();

}


void EXTI3_IRQHandler(void)
{

	EXTI->PR |= (1<<3);
	GP_IRQ_callBack[3]();

}

void EXTI4_IRQHandler(void)
{

	EXTI->PR |= (1<<4);
	GP_IRQ_callBack[4]();

}


void EXTI9_5_IRQHandler(void)
{
	if (EXTI->PR & (1<<5) ) { EXTI->PR |= (1<<5) ; GP_IRQ_callBack[5](); }
	if (EXTI->PR & (1<<6) ) { EXTI->PR |= (1<<6) ; GP_IRQ_callBack[6](); }
	if (EXTI->PR & (1<<7) ) { EXTI->PR |= (1<<7) ; GP_IRQ_callBack[7](); }
	if (EXTI->PR & (1<<8) ) { EXTI->PR |= (1<<8) ; GP_IRQ_callBack[8](); }
	if (EXTI->PR & (1<<9) ) { EXTI->PR |= (1<<9) ; GP_IRQ_callBack[9](); }
}


void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & (1<<10) ) { EXTI->PR |= (1<<10) ; GP_IRQ_callBack[10](); }
	if (EXTI->PR & (1<<11) ) { EXTI->PR |= (1<<11) ; GP_IRQ_callBack[11](); }
	if (EXTI->PR & (1<<12) ) { EXTI->PR |= (1<<12) ; GP_IRQ_callBack[12](); }
	if (EXTI->PR & (1<<13) ) { EXTI->PR |= (1<<13) ; GP_IRQ_callBack[13](); }
	if (EXTI->PR & (1<<14) ) { EXTI->PR |= (1<<14) ; GP_IRQ_callBack[14](); }
	if (EXTI->PR & (1<<15) ) { EXTI->PR |= (1<<15) ; GP_IRQ_callBack[15](); }

}
