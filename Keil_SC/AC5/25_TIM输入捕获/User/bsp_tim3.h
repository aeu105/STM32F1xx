#ifndef __BSP_TIM3_H__
#define __BSP_TIM3_H__


#include <stm32f10x.h>

extern unsigned int High_Val;
extern unsigned char Read_High_Complete_Flag;
extern unsigned int Period;

void TIM3_IC_Configuration(void);


#endif	/* __BSP_TIM3_H_ */
