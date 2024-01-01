#include "main.h"
#include "bsp_systick.h"
#include "bsp_usart1.h"
#include "bsp_dht11.h"


int main()
{
	SysTick_Configuration();
	USART1_Configuration();
	
	DHT11_GPIO_Configuration();
	
	while(1)
	{
		DHT11_Read();
		
		printf("DHT11...\n");
		printf("Temperature = %d.%d℃\nHumidity = %d.%d%%RH\n", Hum_H, Hum_L, Tem_H, Tem_L);
		printf("-------------------------------\n");
		Delay_us(1000000);
	}
}
