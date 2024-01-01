#include "main.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_iic.h"


int main()
{
	int i;
	
	unsigned char WriteBuf[100];
	unsigned char ReadBuf[100];
	
	SysTick_Configuration();
	
	USART1_Configuration();
	
	IIC_Configuration();
	
	for(i = 0; i < 100; i++)
	{
		WriteBuf[i] = 'A';
	}
	
	printf("Write to AT24C02:\n");
	AT24C02_Write_Buf(0, WriteBuf, 100);
	
	printf("Read from AT24C02:\n");
	AT24C02_Read_Buf(0, ReadBuf, 100);
	
	for(i = 0; i < 100; i++)
	{
		printf("%c", ReadBuf[i]);
	}
	
	USART_Cmd(USART1, DISABLE);
	
	while(1)
	{
		//
	}
}
