#include "bsp_dht11.h"


unsigned char Hum_H, Hum_L, Tem_H, Tem_L;	// 全局变量, main() 函数中使用


// PA7: DATA, 单总线, 使用过程中需要改变工作模式
void DHT11_GPIO_Configuration()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DHT11_Mode_Out_PP()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DHT11_Mode_IPU()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DHT11_Start()
{
	unsigned int TimeOut;
	
	DHT11_Mode_Out_PP();	// 将 PA7 配置为输出模式
	
	DHT11_DATA_OUT(0);		// 电平拉低
	Delay_us(20000);		// 保持低电平至少 18ms
	DHT11_DATA_OUT(1);		// 电平拉高
	Delay_us(30);			// 保持高电平 20~40us
	
	DHT11_Mode_IPU();		// 将 PA7 配置为上拉输入模式
	
	// DHT11 80us 低电平响应信号
	TimeOut = 80;
	// 读取低电平并且时间需要 80us
	while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) && (TimeOut > 0))
	{
		TimeOut--;
		Delay_us(1);
	}
	// DHT11 80us 高电平响应信号
	TimeOut = 80;
	// 读取高电平并且时间需要 80us
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) && (TimeOut > 0))
	{
		TimeOut--;
		Delay_us(1);
	}
}

unsigned char DHT11_Read_Byte()
{
	unsigned int i;
	unsigned int TimeOut;
	unsigned char Dat = 0;
	
	DHT11_Mode_IPU();
	
	for(i = 0; i < 8; i++)
	{
		while(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7));	// 50us 低电平开始
		
		Delay_us(40);	// 判断电平
		
		Dat <<= 1;
		if((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)))
			Dat += 1;
		
		TimeOut = 50;
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) && (TimeOut > 0))
		{
			TimeOut--;
			Delay_us(1);
		}
	}
	
	return Dat;
}

void DHT11_Read(void)
{
	unsigned char Hum_H_Temp, Hum_L_Temp, Tem_H_Temp, Tem_L_Temp, Check_Sum;	// 局部变量, 临时
	
	// 启动DHT11
	DHT11_Start();
	
	// 读取数据, 40bit 分 5 次读取
	Hum_H_Temp = DHT11_Read_Byte();
	Hum_L_Temp = DHT11_Read_Byte();
	Tem_H_Temp = DHT11_Read_Byte();
	Tem_L_Temp = DHT11_Read_Byte();
	Check_Sum = DHT11_Read_Byte();
	
	// 发送结束标志
	DHT11_Mode_Out_PP();
	DHT11_DATA_OUT(1);	// 将电平拉高
	
	// 判断读取的数据是否有效(检查校验和)
	if(Check_Sum == (Hum_H_Temp + Hum_L_Temp + Tem_H_Temp + Tem_L_Temp))
	{
		Hum_H = Hum_H_Temp;
		Hum_L = Hum_L_Temp;
		Tem_H = Tem_H_Temp;
		Tem_L = Tem_L_Temp;
	}
}
