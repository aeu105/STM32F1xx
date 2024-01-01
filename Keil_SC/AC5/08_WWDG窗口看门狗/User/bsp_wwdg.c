#include "bsp_wwdg.h"


unsigned char WWDG_CNT = 0x7F;

void WWDG_Configuration(unsigned char tr, unsigned char wr, unsigned int pre) {
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	WWDG_CNT &= tr;	// 防止参数 > 0x7F
	WWDG_SetPrescaler(pre);	// 设置 WWDG 预分频值
	//WWDG_SetCounter(0x7F);	// 设置计数值, 从哪个数开始减
	WWDG_SetWindowValue(wr);	// 设置 WWDG 窗口值
	
	WWDG_NVIC_Configuration();	// 配置 NVIC
	
	// 注意开启位置, 需要在中断使能之前
	WWDG_Enable(WWDG_CNT);	// 使能 WWDG 并装入计数器值
	
	WWDG_ClearFlag();	// 清除早期唤醒中断标志位
	WWDG_EnableIT();	// 使能 WWDG 早期唤醒中断（ EWI）
	
	//WWDG_Enable(WWDG_CNT);	// 使能 WWDG 并装入计数器值
}

void WWDG_NVIC_Configuration(void) {
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
