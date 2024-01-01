#include "bsp_led_configuration.h"
#include "bsp_systick.h"


void LED_Configuration(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void Blinker(void) {
	
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
	Delay_us(20000);
	
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
	Delay_us(1000000);
}
