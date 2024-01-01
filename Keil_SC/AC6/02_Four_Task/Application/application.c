#include "application.h"


// 任务应用, 具体功能实现
void Led1_Task(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}

void Led2_Task(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}

void Led3_Task(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}

void Led4_Task(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}
