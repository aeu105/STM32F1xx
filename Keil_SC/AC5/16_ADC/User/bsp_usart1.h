#ifndef __BSP_USART1_H__
#define __BSP_USART1_H__


#include <stm32f10x.h>
#include <stdio.h>


void GPIOA_USATR1_Configuration(u32 BaudRate);
void USART_SendString(const unsigned char *pt);
void USART1_NVIC_Configuration(void);


#endif	/* __BSP_USART1_H__ */
