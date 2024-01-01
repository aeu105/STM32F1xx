#include "application.h"


extern OS_TCB Task_LED2_TCB;

// 任务应用, 具体功能实现
void Led1_Task(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        Delay_us(2000000);
        //OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        Delay_us(2000000);
        //OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}

void Led2_Task(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_RESET);
        Delay_us(2000000);
        //OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_SET);
        Delay_us(2000000);
        //OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}
