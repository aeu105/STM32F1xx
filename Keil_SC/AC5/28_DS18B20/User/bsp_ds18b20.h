#ifndef __BSP_DS18B20_H__
#define __BSP_DS18B20_H__


#include <stm32f10x.h>
#include "bsp_systick.h"
#include <stdio.h>


#define DS18B20_DATA_OUT(a) GPIO_WriteBit(GPIOB, GPIO_Pin_6, (BitAction)(a))

void DS18B20_GPIO_Configuration(void);
void DS18B20_Init(void);
float DS18B20_Get_Temperature(unsigned int n);
void Read_ID(void);


#endif	/* __BSP_DS18B20_H__ */
