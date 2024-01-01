#include "bsp_init.h"


// 硬件外设初始化

void Bsp_Init(void) {
	
	// 时钟初始化, 1ms 进一次中断
	SysTick_Configuration();
    
    // LED 初始化
    Led_Configuration();
    
    // USART 初始化
    USART_Configuration(115200);
}
