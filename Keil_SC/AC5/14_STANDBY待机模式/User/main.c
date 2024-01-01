#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_gpioa_exti1.h"


int main(void) {
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	PA1_EXTI1_Configuration();
	
	// 开启 RCC_PWR
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	// 使能唤醒管脚 PA0
	// 当 PA0 高电平时唤醒
	PWR_WakeUpPinCmd(ENABLE);
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		Delay_us(200000);
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		Delay_us(200000);
	}
}
