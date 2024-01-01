#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_usart.h"
#include "bsp_matrix_key.h"


int main(void) {
	
	unsigned int Key_num;
	
	SysTick_Configuration();
	
	GPIO_Configuration();
	
	USART1_Configuration(115200);
	
	// Matrix_Key() 函数开启时钟, 放在此处避免频繁开启
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	printf("Matrix_Key\n");
	
	while(1) {
		
		Key_num = Matrix_Key();
		
		if(0 != Key_num) {
			
			printf("Key %d is pressed.\n", Key_num);
		}
	}
}
