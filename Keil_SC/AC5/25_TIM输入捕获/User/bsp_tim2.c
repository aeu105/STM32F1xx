#include "bsp_tim2.h"


void TIM2_OC_Configuration(void) {	// PA1 ���� TIM2_CH2 ����
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	// ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// �����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// ��������: t = nCount * T = 1000 * (1 / (72MHz / 72)) = 1 ms ���ж�
	/*
	TIM_TimeBaseStructure.TIM_Period = 999;	// ����ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 71;	// ��Ƶϵ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// ���ϼ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	*/
	// ��˸Ƶ�� 50Hz, �������� t = 1 / f = 0.02 s = 20 ms
	// ����ֵ: �������� 0.02 s, ��Ƶϵ�� 72, ��ﵽ�������� 0.02 s, ��Ҫ����ֵ 20000
	TIM_TimeBaseStructure.TIM_Period = 19999;	// ����ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 719;	// ��Ƶϵ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// ���ϼ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// ��������ȽϹ���
	/*
	���� TIM_OCMode �Ͳ��� TIM_OCPolarity:
	@1 ��� PWM1 ģʽ:
		1) TIM_OCPolarity_High:
			TIMx_CNT(����ֵ) < TIMx_CCR(�Ƚ�ֵ) ����ߵ�ƽ
			TIMx_CNT > TIMx_CCR ����͵�ƽ
			
		2) TIM_OCPolarity_Low:
			TIMx_CNT < TIMx_CCR ����͵�ƽ
			TIMx_CNT > TIMx_CCR ����ߵ�ƽ
			
	@2 ��� PWM2 ģʽ:
		1) TIM_OCPolarity_High:
			TIMx_CNT < TIMx_CCR ����͵�ƽ
			TIMx_CNT > TIMx_CCR ����ߵ�ƽ
			
		2) TIM_OCPolarity_Low:
			TIMx_CNT < TIMx_CCR ����ߵ�ƽ
			TIMx_CNT > TIMx_CCR ����͵�ƽ
	*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	// ģʽ: �����ߵ͵�ƽ, ��� TIM_OCPolarity ����
	// ���ñȽ�ֵ, ��ռ�ձ�, ������ʵ����Ҫ�ı�ߵ�ƽʱ��, ���ڴ˴�����
	//TIM_OCInitStructure.TIM_Pulse = 10000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);	// ��ʱ�� 2 ͨ�� 2
	
	TIM_Cmd(TIM2, ENABLE);	// ʹ�ܶ�ʱ��
}
