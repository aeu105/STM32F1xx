#include "bsp_gpio_configuration.h"
#include "bsp_systick.h"


void GPIOC_Configuration(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// RCC 时钟使能 GPIOC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	// 上电 PC13引脚 置低
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}

void LED_Blinker(void) {
	
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
	Delay_us(50000);
	
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
	Delay_us(1000000);
}
