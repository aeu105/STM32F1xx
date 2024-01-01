#include "bsp_tim3.h"


void TIM3_IC_Configuration(void) {	// PA6 复用 TIM3_CH1 功能
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// 时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 单次最大测量周期 65.535 ms 不产生溢出中断
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;	// 计数值
	TIM_TimeBaseStructure.TIM_Prescaler = 71;	// 分频系数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 向上计数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	// 输入捕获, 检测到跳变后进入中断 TIM3_IRQHandler
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	// 输入捕获上升沿
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	// 输入捕获来源
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	// 每产生 x 次事件捕获一次
	TIM_ICInitStructure.TIM_ICFilter = 0x0;	// 输入比较滤波器(即前面几个数据不需要, 取值: 0x0~0xF)
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_CC1 | TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_FLAG_Update, ENABLE);	// 电平上升沿跳变进中断 TIM3_IRQHandler
	
	TIM_Cmd(TIM3, ENABLE);	// 使能定时器
}
