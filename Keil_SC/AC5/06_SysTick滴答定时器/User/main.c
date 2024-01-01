#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"


int main(void) {
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		Delay_us(1000000);	// 1s = 1000ms = 1000000us
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		Delay_us(1000000);
	}
}
