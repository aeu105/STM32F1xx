#include "main.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_ds18b20.h"


int main(void) {
	
	unsigned int i;
	
	SysTick_Configuration();
	
	GPIOA_USART1_Configuration(115200);
	
	DS18B20_GPIO_Configuration();
	DS18B20_Init();
	
	while(1) {
		
		//printf("Temperature = %.2f\n", DS18B20_Get_Temperature());
		
		//Read_ID();
		printf("Temperature_%d = %.2f\n", i, DS18B20_Get_Temperature(i));
		i ^= 1;
		
		Delay_us(1000000);
	}
}
