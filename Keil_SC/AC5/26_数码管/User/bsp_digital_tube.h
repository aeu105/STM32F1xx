#ifndef __BSP_DIGITAL_TUBE_H__
#define __BSP_DIGITAL_TUBE_H__


#include <stm32f10x.h>
#include "bsp_systick.h"


extern unsigned int num[];

void Digital_Tube_Configuration(void);
void _74HC595_Configuration(void);
void _74HC595_Send_Data(unsigned char num, unsigned char show_bit);
void _74HC595_Send_Byte(unsigned char Byte);
void Digital_Tube_74HC595_Dispaly(unsigned int Count);


#endif	/* __BSP_DIGITAL_TUBE_H__ */
