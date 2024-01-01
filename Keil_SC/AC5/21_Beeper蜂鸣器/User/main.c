#include "main.h"
#include "bsp_systick.h"
#include "bsp_tim4.h"
#include "bsp_music.h"


int main(void) {
	
	unsigned int i = 0;
	
	SysTick_Configuration();
	
	TIM4_PWMConfiguration();
	
	while(1)
	{
		/*
		Display_Sound(tone[0]);
		Delay_us(1000000);
		Display_Sound(tone[1]);
		Delay_us(1000000);
		Display_Sound(tone[2]);
		Delay_us(1000000);
		Display_Sound(tone[3]);
		Delay_us(1000000);
		Display_Sound(tone[4]);
		Delay_us(1000000);
		Display_Sound(tone[5]);
		Delay_us(1000000);
		Display_Sound(tone[6]);
		Delay_us(1000000);
		*/
		while(little_star[i][0])
		{
			TIM_Cmd(TIM4, ENABLE);
			
			Display_Sound(little_star[i][0]);
			Delay_us(little_star[i][1]);
			
			TIM_Cmd(TIM4, DISABLE);
			Delay_us(20000);	// 关闭定时器延时
			i++;
		}
		i = 0;
		Delay_us(3000000);
	}
}
