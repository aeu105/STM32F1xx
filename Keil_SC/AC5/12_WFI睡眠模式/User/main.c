#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_gpioa_exti0.h"


int main(void) {
	
	unsigned int nCount;
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	PA0_EXTI0_Configuration();
	
	while(1) {
		
		// 延时 1s 闪烁
		for(nCount = 0; nCount < 5; nCount++) {
			
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
			Delay_us(1000000);
			
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
			Delay_us(1000000);
		}
		
		// WFI	睡眠模式	任一[中断]唤醒
		__WFI();
		
		// 延时 200ms 闪烁
		for(nCount = 0; nCount < 5; nCount++) {
			
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
			Delay_us(200000);
			
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
			Delay_us(200000);
		}
	}
}
