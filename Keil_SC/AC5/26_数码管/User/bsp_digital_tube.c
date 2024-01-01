#include "bsp_digital_tube.h"


unsigned int num[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF, 0x00};

void Digital_Tube_Configuration(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 \
								| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// SCLK: PB13	RCLK: PB12	DIO: PB15
void _74HC595_Configuration(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// 上升沿数据发送, 此处引脚置低电平
	GPIO_WriteBit(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15, Bit_RESET);
}

// 数据并出
void _74HC595_Send_Data(unsigned char num, unsigned char show_bit) {
	
	_74HC595_Send_Byte(num);
	_74HC595_Send_Byte(1 << show_bit);
	
	GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
	Delay_us(10);
	GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
	Delay_us(10);
}

// 数据串入
void _74HC595_Send_Byte(unsigned char Byte) {
	
	unsigned int i;
	
	// 先写高位
	for(i = 0; i < 8; i++) {
		
		if(Byte & 0x80)
			GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_SET);
		else
			GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_RESET);
		
		GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);
		Delay_us(10);
		
		GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);
		Delay_us(10);
		
		Byte <<= 1;
	}
}

void Digital_Tube_74HC595_Dispaly(unsigned int Count) {
	
	static unsigned int thousand_bit, hundred_bit, ten_bit, single_bit;
	
	thousand_bit = Count / 1000;
	hundred_bit = (Count % 1000) / 100;
	ten_bit = ((Count % 1000) % 100) / 10;
	single_bit = ((Count % 1000) % 100) % 10;
	
	_74HC595_Send_Data(num[single_bit], 0);
	_74HC595_Send_Data(num[ten_bit], 1);
	_74HC595_Send_Data(num[hundred_bit], 2);
	_74HC595_Send_Data(num[thousand_bit], 3);
}
