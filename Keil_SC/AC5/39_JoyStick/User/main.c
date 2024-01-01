#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_usart.h"
#include "bsp_joystick.h"


int main(void) {
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	
	USART_Configuration(115200);
	
	JoyStick_Configuration();
	
	while(1) {
		
		LED_Blinker();
		JoyStick_Scan();
	}
}
