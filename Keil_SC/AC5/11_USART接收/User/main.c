#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_usart1.h"


int main(void) {
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	
	GPIOA_USATR1_Configuration(115200);
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		Delay_us(1000000);
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		Delay_us(1000000);
	}
}
