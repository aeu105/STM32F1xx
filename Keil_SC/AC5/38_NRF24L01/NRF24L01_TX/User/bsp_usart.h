#ifndef __BSP_USART_H__
#define __BSP_USART_H__


#include <stm32f10x.h>
#include <stdio.h>


void USART_Configuration(u32 BaudRate);
void USART_SendString(unsigned char *pt);


#endif	/* __BSP_USART_H__ */
