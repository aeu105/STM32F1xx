#include "bsp_iwdg.h"


void IWDG_Configuration(void) {
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	// 使能对寄存器 IWDG_PR 和 IWDG_RLR 的写操作
	IWDG_SetPrescaler(IWDG_Prescaler_64);	// 设置 IWDG 预分频值
	IWDG_SetReload(625);	// 设置 IWDG 重装载值, 1s 不进行重装载则产生复位
	IWDG_ReloadCounter();	// 按照 IWDG 重装载寄存器的值重装载 IWDG 计数器
	IWDG_Enable();	// 使能 IWDG, 即刻开始计数
}
