#ifndef __BSP_IIC_H__
#define __BSP_IIC_H__


#include <stm32f10x.h>
#include "bsp_systick.h"


#define SDA_OUT()	{GPIOB->CRL &= 0x0FFFFFFF; GPIOB->CRL |= 0x30000000;}
#define SDA_IN()	{GPIOB->CRL &= 0x0FFFFFFF; GPIOB->CRL |= 0x40000000;}

#define IIC_SCL_H	GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET)
#define IIC_SCL_L	GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET)

#define IIC_SDA_H	GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET)
#define IIC_SDA_L	GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET)

#define Read_SDA	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)


void IIC1_Configuration(void);
void IIC_START(void);
void IIC_STOP(void);
unsigned int IIC_Wait_ACK(void);
void IIC_ACK(void);
void IIC_Send_Byte(unsigned char dat);
unsigned char IIC_Receive_Byte(void);


#endif	/* __BSP_IIC_H__ */
