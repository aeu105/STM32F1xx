#include "main.h"
#include "bsp_systick.h"
#include "bsp_led_configuration.h"
#include "bsp_usart.h"


int main(void) {
	
	SysTick_Configuration();
	
	// ∞Â‘ÿLED(PC13)
	LED_Configuration();
	
	USART1_Configuration(115200);
	
	while(1) {
		
		Blinker();
		printf("USART1\n");
	}
}
