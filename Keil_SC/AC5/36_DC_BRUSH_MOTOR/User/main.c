#include "main.h"
#include "bsp_systick.h"
#include "bsp_key.h"
#include "bsp_dc_brush_motor.h"
#include "bsp_adc.h"


int main(void)
{
	//unsigned int i;
	
	SysTick_Configuration();
	
	Key_Configuration();
	
	ADC1_CH6_Configuration();
	
	DC_Brush_Motor_Configuration();
	
	STBY_H;
	AIN1_H;
	AIN2_L;	// ��ת
	
	// PB6, PB7 ������ģʽ
	Encoder_Init_TIM4();
	
	TIM3_Base_Configuration();
	
	TIM_Cmd(TIM2, ENABLE);
	//TIM_SetCompare2(TIM2, 100);	// ���ռ�ձ�100%
	
	while(1)
	{
		// ADC_ConvertVal ȡֵ��Χ: 0~4096
		// ռ�ձ�ȡֵ��Χ: 0~100
		TIM_SetCompare2(TIM2, ADC_ConvertVal / 40);
		
		/*
		// ����
		for(i = 0; i < 100; i++)
		{
			TIM_SetCompare2(TIM2, i);
			Delay_us(100000);
		}
		// ����
		for(i = 100; i > 0; i--)
		{
			TIM_SetCompare2(TIM2, i);
			Delay_us(100000);
		}
		*/
		/*
		// ��ͣ����
		if(Key_Scan(GPIOA, GPIO_Pin_0) == KEY_ON)
		{
			GPIOA->ODR ^= 0x04;	// AIN1/AIN2 ��ͬʱֹͣ
		}
		*/
		/*
		// ����ת
		if(Key_Scan(GPIOA, GPIO_Pin_5) == KEY_ON)
		{
			GPIOA->ODR ^= GPIO_Pin_2 | GPIO_Pin_3;
		}
		*/
	}
}
