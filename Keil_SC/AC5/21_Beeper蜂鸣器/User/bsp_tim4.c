#include "bsp_tim4.h"


void TIM4_PWMConfiguration(void) {	// PB8 <--> TIM4_CH3
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// ���� 1 kHz ����
	//TIM_TimeBaseStructure.TIM_Period = 999;
	// ���� 523 Hz ����
	/* ���㷽ʽ:
	// ���������� Do ������, Ƶ��Ϊ 523 Hz
	// �� t1 = 1 / 523 Hz
	// STM32 ʱ�����:
	// t2 = nCount * (1 / (f / Pre)) = nCount * (1 / (72 MHz / 72))
	// t1 = t2
	// 1 / 523 Hz = nCount / 1 MHz
	// nCount = 1 MHz / 523 Hz = 1912
	*/
	//TIM_TimeBaseStructure.TIM_Period = 1912;
	TIM_TimeBaseStructure.TIM_Period = 71;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 50% ռ�ձ�
	TIM_OCInitStructure.TIM_Pulse = 500;
	//TIM_OCInitStructure.TIM_Pulse = 1912 / 2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	
	// ʹ��ǰʹ�ܶ�ʱ��
	// TIM_Cmd(TIM4, ENABLE);	
}
