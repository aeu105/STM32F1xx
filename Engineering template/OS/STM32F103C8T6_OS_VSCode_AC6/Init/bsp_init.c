#include "bsp_init.h"


// 硬件外设初始化
void bsp_Init(void) {

    // 时钟初始化, 1ms 进一次中断
    SysTick_Configuration();
    
}
