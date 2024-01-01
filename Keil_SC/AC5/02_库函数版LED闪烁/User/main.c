#include "main.h"


void Delay_us(unsigned long nCount);
void GPIOC_Configuration(void);


int main(void) {
	
	// 配置 GPIOC 初始化
	GPIOC_Configuration();
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		Delay_us(1000000);
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		Delay_us(1000000);
	}
}

void Delay_us(unsigned long nCount) {
	
	while(nCount--);
}

void GPIOC_Configuration(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// RCC 时钟使能 GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
