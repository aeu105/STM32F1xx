#ifndef __BSP_TCS3200_H__
#define __BSP_TCS3200_H__


#include <stm32f10x.h>
#include <stdio.h>
#include "bsp_systick.h"


extern unsigned int amount;


void TCS3200_Configuration(unsigned int s0, unsigned int s1);
void PA4_EXTI4_Configuration(void);
void White_Balance(void);
unsigned int TCS3200_Red(void);
unsigned int TCS3200_Green(void);
unsigned int TCS3200_Blue(void);


#endif	/* __BSP_TCS3200_H__ */
