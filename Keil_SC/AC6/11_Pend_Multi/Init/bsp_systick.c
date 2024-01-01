#include "bsp_systick.h"


void SysTick_Configuration(void) {
	
	// 72000000 / 1000u = 72000
	while(SysTick_Config(SystemCoreClock / OS_CFG_TICK_RATE_HZ));	// 初始化使能定时器, 1ms 进一次中断
	/*
	while(SysTick_Config(72000));	// 初始化使能定时器, 1ms 进一次中断
	*/
}

void Delay_us(unsigned long nCount) {
    
    while(nCount--) {
        
        //
    }
}
