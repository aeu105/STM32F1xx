#include "main.h"
#include "bsp_systick.h"
#include "bsp_led_configuration.h"
#include "bsp_tim2.h"


int main(void) {
	
	//unsigned int i;
	
	SysTick_Configuration();
	
	GPIO_Configuration();
	
	TIM2_PWMConfiguration();
	
	
	while(1)
	{
		//Blinker();
		/*
		while(1)
		{
			// ���� ��Ч��
			// �ɰ�����
			for(i = 0; i < TIM_TIME; i++)	// i ���ȡֵ�ɼ������ھ���(20000)
			{
				TIM_SetCompare2(TIM2, i);	// ���ñȽ�ֵ(�ı�ռ�ձ�ʱ��)
				Delay_us(20);
			}
			// �����䰵
			for(i = TIM_TIME; i > 0; i--)
			{
				TIM_SetCompare2(TIM2, i);
				Delay_us(20);
			}
		}
		*/
		while(1)
		{
			// �������
			TIM_SetCompare2(TIM2, 500);	// 0.5 ms <--> 0��
			Delay_us(500000);
			TIM_SetCompare2(TIM2, 1000);	// 1 ms <--> 45��
			Delay_us(500000);
			TIM_SetCompare2(TIM2, 1500);	// 1.5 ms <--> 90��
			Delay_us(500000);
			TIM_SetCompare2(TIM2, 2000);	// 2 ms <--> 135��
			Delay_us(500000);
			TIM_SetCompare2(TIM2, 2500);	// 2.5 ms <--> 180��
			Delay_us(500000);
			TIM_SetCompare2(TIM2, 2000);	// 2 ms <--> 135��
			Delay_us(500000);
			TIM_SetCompare2(TIM2, 1500);	// 1.5 ms <--> 90��
			Delay_us(500000);
			TIM_SetCompare2(TIM2, 1000);	// 1 ms <--> 45��
			Delay_us(500000);
		}
	}
}
