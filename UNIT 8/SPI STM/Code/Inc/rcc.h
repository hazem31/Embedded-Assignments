

#ifndef RCC_H_
#define RCC_H_

#include "stm32f103x6.h"


#define HSI_RC_CLK		(uint32_t)8000000
#define HSE_Clock		(uint8_t)160000000

uint32_t MCAL_RCC_GetSYS_CLKFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);


#endif
