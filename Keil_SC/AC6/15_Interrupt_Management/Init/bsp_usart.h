#ifndef __BSP_USART_H__
#define __BSP_USART_H__


#include <stm32f10x.h>
#include <stdio.h>


void USART_Configuration(uint32_t BaudRate);
void USART_NVIC_Configuration(void);


#endif  /* __BSP_USART_H__ */
