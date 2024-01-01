#include "bsp_iic.h"

void IIC_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// PB6: SCL	PB7: SDA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// SCL 高电平时可写数据?
	GPIO_WriteBit(GPIOB, GPIO_Pin_6 | GPIO_Pin_7, Bit_RESET);
}

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

void IIC_Write_Byte(unsigned char Addr, unsigned char Dat)
{
	IIC_START();
	IIC_Send_Byte(0xA0);	// 发送设备地址
	while(IIC_Wait_ACK());	// 等待外设应答
	IIC_Send_Byte(Addr);	// 发送写入数据的地址
	while(IIC_Wait_ACK());
	IIC_Send_Byte(Dat);
	while(IIC_Wait_ACK());
	IIC_STOP();
}

// Page 写操作
void AT24C02_Write_Page(unsigned char Addr, unsigned char *buf)
{
	unsigned int size = 8;
	
	IIC_START();
	IIC_Send_Byte(0xA0);
	while(IIC_Wait_ACK());
	IIC_Send_Byte(Addr);
	while(IIC_Wait_ACK());
	
	while(size--)
	{
		IIC_Send_Byte(*buf);
		while(IIC_Wait_ACK());
		buf++;	// 数据指针增加
		Addr++;	// 地址增加
	}
	IIC_STOP();
}

void AT24C02_Write_Buf(unsigned char Addr, unsigned char *buf, unsigned int size)
{
	while(size--)
	{
		IIC_Write_Byte(Addr, *buf);
		buf++;
		Addr++;
	}
}

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

unsigned char IIC_Read_Byte(unsigned char Addr)
{
	unsigned char Dat;
	
	IIC_START();
	IIC_Send_Byte(0xA0);
	while(IIC_Wait_ACK());
	IIC_Send_Byte(Addr);
	while(IIC_Wait_ACK());
	
	IIC_START();
	IIC_Send_Byte(0xA1);
	while(IIC_Wait_ACK());
	
	Dat = IIC_Receive_Byte();
	
	IIC_STOP();
	
	return Dat;
}

void AT24C02_Read_Buf(unsigned char Addr, unsigned char *buf, unsigned int size)
{
	IIC_START();
	IIC_Send_Byte(0xA0);
	while(IIC_Wait_ACK());
	IIC_Send_Byte(Addr);
	while(IIC_Wait_ACK());
	
	IIC_START();
	IIC_Send_Byte(0xA1);
	while(IIC_Wait_ACK());
	while(size > 1)
	{
		*buf = IIC_Receive_Byte();
		IIC_ACK();
		buf++;
		Addr++;
		size--;
	}
	
	*buf = IIC_Receive_Byte();
	
	IIC_STOP();
}
