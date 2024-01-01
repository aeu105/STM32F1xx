#ifndef __BSP_DMA1_H__
#define __BSP_DMA1_H__


#include <stm32f10x.h>

#define SENDBUFF_SIZE   100


extern unsigned char SendBuff[SENDBUFF_SIZE];


void DMA1_Configuration(void);


#endif	/* __BSP_DMA1_H__ */
