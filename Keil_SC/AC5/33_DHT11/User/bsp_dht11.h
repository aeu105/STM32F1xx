#ifndef __BSP_DHT11_H__
#define __BSP_DHT11_H__


#include <stm32f10x.h>
#include "bsp_systick.h"


#define DHT11_DATA_OUT(a) GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)(a))

extern unsigned char Hum_H, Hum_L, Tem_H, Tem_L;

void DHT11_GPIO_Configuration(void);
void DHT11_Read(void);


#endif
