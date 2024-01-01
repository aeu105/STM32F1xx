#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__


#include <stm32f10x.h>

#define CS_LOW	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET)
#define CS_HIGH	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET)


void SPI1_Configuration(void);
u16 SPI1_Read(void);


#endif	/* __BSP_SPI_H__ */
