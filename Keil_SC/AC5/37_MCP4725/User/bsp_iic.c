#include "bsp_iic.h"


// 引脚配置
// PB6: SCL	PB7: SDA
void IIC1_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// SCL 高电平时可写数据
	GPIO_WriteBit(GPIOB, GPIO_Pin_6 | GPIO_Pin_7, Bit_RESET);
}

// 开始
void IIC_START(void)
{
	// SDA 配置为输出
	SDA_OUT();
	
	IIC_SDA_H;
	IIC_SCL_H;
	Delay_us(5);
	
	IIC_SDA_L;
	IIC_SCL_L;
}

// 停止
void IIC_STOP(void)
{
	// SDA 配置为输出
	SDA_OUT();
	
	IIC_SDA_L;
	IIC_SCL_H;
	Delay_us(5);
	
	IIC_SDA_H;
	IIC_SCL_L;
	
	// 两次写操作的间隔
	Delay_us(10000);
}

// STM32 等待应答信号(有应答0, 无应答1)
unsigned int IIC_Wait_ACK(void)
{
	unsigned int n = 0;
	
	SDA_IN();
	IIC_SCL_H;
	
	// 等待应答, 有应答引脚输出低电平
	while(Read_SDA)
	{
		n++;
		if(n > 500)
		{
			IIC_STOP();
			return 1;
		}
		
	}
	
	IIC_SCL_L;
	
	return 0;
}

// STM32 应答外设
void IIC_ACK(void)
{
	SDA_OUT();
	
	IIC_SCL_L;
	IIC_SDA_H;
	IIC_SCL_H;
	
	IIC_SCL_L;
}

// 发送字节
void IIC_Send_Byte(unsigned char dat)
{
	unsigned  int i;
	
	SDA_OUT();
	
	for(i = 0; i < 8; i++)
	{
		if(dat & 0x80)
			IIC_SDA_H;
		else
			IIC_SDA_L;
		
		IIC_SCL_L;
		IIC_SCL_H;
		
		IIC_SCL_L;
		
		dat <<= 1;
	}
}

// 读取字节
unsigned char IIC_Receive_Byte(void)
{
	unsigned int i;
	unsigned char Dat;
	
	SDA_IN();
	
	// 读数据, 先读高位
	for(i = 0; i < 8; i++)
	{
		IIC_SCL_L;
		IIC_SCL_H;
		
		Dat <<= 1;	// 注意此句位置
		
		if(Read_SDA)
		{
			Dat++;
		}
		
		IIC_SCL_L;
	}
	
	return Dat;
}
