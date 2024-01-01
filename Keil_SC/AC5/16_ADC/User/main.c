#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_usart1.h"
#include "bsp_adc.h"


int main(void) {
	
	float Temperature;
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	
	GPIOA_USATR1_Configuration(115200);
	
	ADC1_Configuration();
	
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	//DMA_Cmd(DMA1_Channel1, ENABLE);
	
	while(1) {
		
		Blinker();
		
		printf("V25 = %.2f\n", V25);
		printf("ADC_ConvertVal = %.2f\n", (float)ADC_ConvertVal);
		printf("AVG_SLOPE = %.2f\n", AVG_SLOPE);
		
		Temperature = (V25 - ADC_ConvertVal) / AVG_SLOPE + 25;
		Delay_us(1000000);
		printf("Temperature = %.3f¡æ\n", Temperature);
	}
}
