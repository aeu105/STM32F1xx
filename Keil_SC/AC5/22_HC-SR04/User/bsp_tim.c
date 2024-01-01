#include "bsp_tim.h"


void TIM2_BaseConfiguration(void) {
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// ��ʱ��, �������ü���ֵ�������������ж�
	// Period ȡֵ��Χ: 0x0000 ~ 0xFFFF
	// 72 ��Ƶ, ����ʱ 65535 us(0.065535 s ��������)
	// s = v * t = 340m/s * 0.065535s = 22.2819 m
	// �ɲ������� s = s/2 = 11.14095 m, ��ֵԶ����ģ��������ȷ�Χ(0~400 cm)
	// ������ʹ�ù�����, ����ֵ����Ƶ����ֵ, ����Ҫ�ж�
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;	// 65535
	TIM_TimeBaseStructure.TIM_Prescaler = 71;	// 72 ��Ƶ, ��һ������ʱ 1us
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_Cmd(TIM2, ENABLE);
	
	// ʹ��ǰʱ����
	//TIM_Cmd(TIM2, DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);
}
