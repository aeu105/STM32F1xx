#include "main.h"
#include "bsp_systick.h"
#include "stdio.h"
#include "bsp_led_configuration.h"
#include "bsp_usart.h"
#include "bsp_tim2.h"
#include "bsp_tim3.h"


int main(void) {
	
	SysTick_Configuration();
	
	GPIO_Configuration();
	
	//GPIOA_USART1_Configuration();	// !!!
	
	TIM2_OC_Configuration();
	TIM3_IC_Configuration();	// 采集时 TIM2 已经开始发出高电平, 因此第一个数值会有差

	GPIOA_USART1_Configuration(115200);	// 注意 USART 初始化位置
	
	TIM_SetCompare2(TIM2, 15000);	// 发出脉冲: 周期 20ms, 50% 占空比
	
	while(1) {
		
//		Blinker();
		
		if(1 == Read_High_Complete_Flag) {
			
			printf("High_Val = %d us\n", High_Val);
			Read_High_Complete_Flag = 0;
		}
		
		Delay_us(100000);
	}
}
