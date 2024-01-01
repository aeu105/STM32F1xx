#include "bsp_tim2.h"


void TIM2_OC_Configuration(void) {	// PA1 复用 TIM2_CH2 功能
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	// 时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 计数周期: t = nCount * T = 1000 * (1 / (72MHz / 72)) = 1 ms 进中断
	/*
	TIM_TimeBaseStructure.TIM_Period = 999;	// 计数值
	TIM_TimeBaseStructure.TIM_Prescaler = 71;	// 分频系数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	*/
	// 闪烁频率 50Hz, 计数周期 t = 1 / f = 0.02 s = 20 ms
	// 计数值: 计数周期 0.02 s, 分频系数 72, 则达到计数周期 0.02 s, 需要计数值 20000
	TIM_TimeBaseStructure.TIM_Period = 19999;	// 计数值
	TIM_TimeBaseStructure.TIM_Prescaler = 719;	// 分频系数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// 配置输出比较功能
	/*
	参数 TIM_OCMode 和参数 TIM_OCPolarity:
	@1 如果 PWM1 模式:
		1) TIM_OCPolarity_High:
			TIMx_CNT(计数值) < TIMx_CCR(比较值) 输出高电平
			TIMx_CNT > TIMx_CCR 输出低电平
			
		2) TIM_OCPolarity_Low:
			TIMx_CNT < TIMx_CCR 输出低电平
			TIMx_CNT > TIMx_CCR 输出高电平
			
	@2 如果 PWM2 模式:
		1) TIM_OCPolarity_High:
			TIMx_CNT < TIMx_CCR 输出低电平
			TIMx_CNT > TIMx_CCR 输出高电平
			
		2) TIM_OCPolarity_Low:
			TIMx_CNT < TIMx_CCR 输出高电平
			TIMx_CNT > TIMx_CCR 输出低电平
	*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	// 模式: 决定高低电平, 结合 TIM_OCPolarity 配置
	// 设置比较值, 即占空比, 呼吸灯实现需要改变高电平时间, 不在此处设置
	//TIM_OCInitStructure.TIM_Pulse = 10000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);	// 定时器 2 通道 2
	
	TIM_Cmd(TIM2, ENABLE);	// 使能定时器
}
