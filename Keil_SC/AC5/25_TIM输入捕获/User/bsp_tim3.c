#include "bsp_tim3.h"


void TIM3_IC_Configuration(void) {	// PA6 ���� TIM3_CH1 ����
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// �������������� 65.535 ms ����������ж�
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;	// ����ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 71;	// ��Ƶϵ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// ���ϼ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	// ���벶��, ��⵽���������ж� TIM3_IRQHandler
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	// ���벶��������
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	// ���벶����Դ
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	// ÿ���� x ���¼�����һ��
	TIM_ICInitStructure.TIM_ICFilter = 0x0;	// ����Ƚ��˲���(��ǰ�漸�����ݲ���Ҫ, ȡֵ: 0x0~0xF)
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_CC1 | TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_FLAG_Update, ENABLE);	// ��ƽ������������ж� TIM3_IRQHandler
	
	TIM_Cmd(TIM3, ENABLE);	// ʹ�ܶ�ʱ��
}
