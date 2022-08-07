/*
 * gpio.h
 *
 * Created: 09/05/2022 04:29:52 م
 *  Author: hazem
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "Atmega32.h"

//Config Structure

typedef struct
{
	uint8_t GPIO_PinNumber ; // Specifies the GPIO pins to be configured.
	// This parameter must be set based on @ref GPIO_PINS_define

	uint8_t  GPIO_MODE      ; // Specifies the operating mode for the selected pins
	// This parameter can be a value of @ref GPIO_MODE_define

}GPIO_PinConfig_t;

//@ref GPIO_PIN_state
#define GPIO_PIN_SET    	1
#define GPIO_PIN_RESET     0

//================================
//Macros Configuration References
//================================

// @ref GPIO_PINS_define
#define GPIO_PIN_0                 ((uint8_t)0x01)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint8_t)0x02)  /* Pin 1 selected  10  */
#define GPIO_PIN_2                 ((uint8_t)0x04)  /* Pin 2 selected  100  */
#define GPIO_PIN_3                 ((uint8_t)0x08)  /* Pin 3 selected  1000  */
#define GPIO_PIN_4                 ((uint8_t)0x10)  /* Pin 4 selected  10000  */
#define GPIO_PIN_5                 ((uint8_t)0x20)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint8_t)0x40)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint8_t)0x80)  /* Pin 7 selected    */
#define GPIO_PIN_All               ((uint8_t)0xFF)  /* All pins selected */

//@ref GPIO_MODE_define

#define  GPIO_MODE_INPUT_FLO                     0x00000001u   //Floating input
#define  GPIO_MODE_INPUT_PU                      0x00000002u   //Input with pull-up
#define  GPIO_MODE_OUTPUT_PP                     0x00000003u   //General purpose output push-pull


// default is enabled
void MCAL_disable_Pull_up();
void MCAL_enable_Pull_up();

void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig_t* PinConfig);
void MCAL_GPIO_DeInit (GPIO_TypeDef *GPIOx);

uint8_t MCAL_GPIO_ReadPin (GPIO_TypeDef *GPIOx,uint8_t PinNumber );
uint8_t MCAL_GPIO_ReadPort (GPIO_TypeDef *GPIOx);

void MCAL_GPIO_WritePin (GPIO_TypeDef *GPIOx,uint8_t PinNumber , uint8_t Value);
void MCAL_GPIO_WritePort (GPIO_TypeDef *GPIOx , uint8_t Value);

void MCAL_GPIO_TogglePin (GPIO_TypeDef *GPIOx,uint8_t PinNumber );


#endif /* GPIO_H_ */