#include "bsp_ds18b20.h"


// 设备 ID 号
unsigned char ds18b20_id[2][8] = {
	
	0x28, 0xFF, 0x64, 0x2E, 0x31, 0x18, 0x02, 0x70,
	0x28, 0xB5, 0x07, 0x79, 0xA2, 0x00, 0x03, 0xC3,
};

void DS18B20_Mode_Out_PP(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DS18B20_Mode_IPU(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// PB6: DS18B20_DQ
void DS18B20_GPIO_Configuration(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// DS18B20 初始化
void DS18B20_Init(void) {
	
	// PB6 配置为输出模式
	DS18B20_Mode_Out_PP();
	
	// 输出低电平
	DS18B20_DATA_OUT(0);
	// 延时 > 480us
	Delay_us(750);
	
	// 输出高电平
	DS18B20_DATA_OUT(1);
	
	Delay_us(15);
	
	// PB6 配置为上拉输入
	DS18B20_Mode_IPU();
	
	// 等待低电平
	while(0 != GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6));
	
	// 等待低电平结束
	while(0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6));
}


void DS18B20_Write_Byte(unsigned char Data) {
	
	unsigned int i;
	
	DS18B20_Mode_Out_PP();
	
	for(i = 0; i < 8; i++) {
		
		// 先写低位
		if(Data & 0x01) {	// 写 1
			
			DS18B20_DATA_OUT(0);
			Delay_us(8);
			
			DS18B20_DATA_OUT(1);
			Delay_us(58);
		}
		else {	// 写 0
			
			DS18B20_DATA_OUT(0);
			Delay_us(70);
		
			DS18B20_DATA_OUT(1);
			Delay_us(2);
		}
		
		Data = Data >> 1;
	}
}

unsigned char DS18B20_Read_Byte(void) {
	
	unsigned int i;
	unsigned char Data = 0;
	
	DS18B20_Mode_Out_PP();
	
	for(i = 0; i < 8; i++) {
		
		DS18B20_Mode_Out_PP();
		DS18B20_DATA_OUT(0);
		Delay_us(10);
		DS18B20_Mode_IPU();
		
		Data |= (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) << i);
		Delay_us(55);
	}
	
	return Data;
}

float DS18B20_Get_Temperature(unsigned int n) {
	
	unsigned int i;
	unsigned char tp_lsb, tp_msb;
	short s_tp;
	float Temperature;
	
	DS18B20_Init();
	//DS18B20_Write_Byte(0xCC);
	
	DS18B20_Write_Byte(0x55);
	// 发送 ID
	for(i = 0; i < 8; i++) {
		
		DS18B20_Write_Byte(ds18b20_id[n][i]);
	}
	
	DS18B20_Write_Byte(0x44);
	
	
	DS18B20_Init();
	DS18B20_Write_Byte(0x55);
	
	for(i = 0; i < 8; i++) {
		
		DS18B20_Write_Byte(ds18b20_id[n][i]);
	}
	
	DS18B20_Write_Byte(0xBE);
	
	// 先读低位, 再读高位
	tp_lsb = DS18B20_Read_Byte();
	tp_msb = DS18B20_Read_Byte();
	
	s_tp = (tp_msb << 8);
	s_tp |= tp_lsb;
	
	if(s_tp < 0)	// 负温度值
		Temperature = 0 - ((~s_tp + 1) * 0.0625);
	else
		Temperature = s_tp * 0.0625;
	
	return Temperature;
}

void Read_ID(void) {
	
	unsigned int i;
	unsigned char Dat[8];
	
	DS18B20_Init();
	DS18B20_Write_Byte(0x33);
	
	for(i = 0; i < 8; i++) {
		
		Dat[i] = DS18B20_Read_Byte();
		
		printf("ID: %c", Dat[i]);
	}
}
