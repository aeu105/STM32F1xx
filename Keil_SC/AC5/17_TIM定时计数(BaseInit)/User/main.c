#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_tim2.h"


int main(void) {
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	
	TIM2_BaseConfiguration();
	
	// 初始化时 TIM2 时钟已关闭, 使用前开启
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	while(1) {
		
	}
}
