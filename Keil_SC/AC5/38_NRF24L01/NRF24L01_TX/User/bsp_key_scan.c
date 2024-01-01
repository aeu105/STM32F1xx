#include "bsp_key_scan.h"
#include "bsp_systick.h"


void GPIOA_Configuration(void) {
	
	// PA0 -- Key
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int Key_Scan(void) {
	
	if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
		
		Delay_us(10000);	// ��ʱ 10ms
		
		if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
			return KEY_ON;	// ��������, ���� 1
		
		return KEY_OFF;
	}	
	return KEY_OFF;	
}
