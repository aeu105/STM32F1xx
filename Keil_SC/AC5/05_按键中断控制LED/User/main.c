#include "main.h"
#include "bsp_gpio_configuration.h"
#include "bsp_gpioa_exti0.h"


int main(void) {
	
	GPIOC_Configuration();
	
	PA0_EXTI0_Configuration();
	
	while(1) {
		
		//
	}
}
