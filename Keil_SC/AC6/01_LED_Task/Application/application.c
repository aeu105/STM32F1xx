#include "application.h"


// 任务应用, 具体功能实现
void Led_Task(void *p_arg) {	// 内部循环实现具体功能
    
    OS_ERR err;
	
	(void)p_arg;
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        // OSTimeDly(1, OS_OPT_TIME_DLY, &err); // 此函数延时一个时钟节拍 ms
        OSTimeDly(1000, OS_OPT_TIME_DLY, &err); // 相对延时 1 s
	}
}
