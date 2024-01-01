#include "bsp_stepper_motor.h"


// PA1: TIM2_CH2
void STEPPER_MOTOR_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStrcuture;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// 周期 7500us
	// 1min -> 360°
	// 不在此处设置周期
	TIM_TimeBaseStructure.TIM_Period = 0;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);
	
	TIM_OCInitStrcuture.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStrcuture.TIM_Pulse = 0;
	TIM_OCInitStrcuture.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStrcuture.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM2, &TIM_OCInitStrcuture);
	
	// 设置主模式
	TIM_SelectMasterSlaveMode(TIM2, ENABLE);
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
	
	// TIM_Cmd(TIM2, ENABLE);
}
// 从模式定时器
void TIM4_CNT_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	// 需要计数的个数
	TIM_TimeBaseStructure.TIM_Period = 0;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	// 注意此处不分频, 频率来源 TIM2
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, & TIM_TimeBaseStructure);
	
	// 时钟来源
	TIM_SelectInputTrigger(TIM4, TIM_TS_ITR1);
	// 设置从模式, 时钟触发来源
	TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_External1);
	
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	
	//TIM_Cmd(TIM4, ENABLE);
}

// PA2: Dir
void Dir_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// speed: 1rpm ~ 100rpm
// 1min 转 n 圈
void Set_Speed_RPM(unsigned int speed)
{
	unsigned int Period;
	
	Period = ((1.8 * 1000000) / (speed * 6 * 40));
	
	TIM_SetAutoreload(TIM2, (Period - 1));
	TIM_SetCompare2(TIM2, (Period / 2) - 1);
}
// rpm: 每分钟电机转的圈数	Pulsenum: 发送的脉冲个数
void Pulse_Output(unsigned int rpm, unsigned int Pulsenum)
{
	Set_Speed_RPM(rpm);
	TIM_SetAutoreload(TIM4, Pulsenum - 1);
	
	// 先开接收, 再开发送
	TIM_Cmd(TIM4, ENABLE);
	Delay_us(1000);	// 保证 TIM4 准备就绪
	TIM_Cmd(TIM2, ENABLE);
}
