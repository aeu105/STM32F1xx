#include "bsp_gpio_configuration.h"
#include "bsp_systick.h"


void GPIO_Configuration()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}


void GPIO_Blink()
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);	// LED �õ�
	Delay_us(50000);	// ��ʱ 50ms
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);	// LED �ø�
	Delay_us(1000000);	// ��ʱ 1s
}
