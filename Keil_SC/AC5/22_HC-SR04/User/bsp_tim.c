#include "bsp_tim.h"


void TIM2_BaseConfiguration(void) {
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 定时器, 超出设置计数值后会产生并进入中断
	// Period 取值范围: 0x0000 ~ 0xFFFF
	// 72 分频, 最大耗时 65535 us(0.065535 s 会产生溢出)
	// s = v * t = 340m/s * 0.065535s = 22.2819 m
	// 可测最大距离 s = s/2 = 11.14095 m, 此值远大于模块测量精度范围(0~400 cm)
	// 此例程使用过程中, 计数值不会计到最大值, 不需要中断
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;	// 65535
	TIM_TimeBaseStructure.TIM_Prescaler = 71;	// 72 分频, 计一个数用时 1us
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_Cmd(TIM2, ENABLE);
	
	// 使用前时开启
	//TIM_Cmd(TIM2, DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);
}
