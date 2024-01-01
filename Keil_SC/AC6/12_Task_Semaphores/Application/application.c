#include "application.h"


extern OS_TCB Task2_TCB;

// 任务应用, 具体功能实现
void Task_1(void *p_arg) {
    
    OS_ERR err;
    
	(void)p_arg;
	
    while(1) {
        
        if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
            
            OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);
            if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
                
                // 任务信号量发送给任务2
                OSTaskSemPost(&Task2_TCB, OS_OPT_POST_NONE, &err);
            }
        }
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

void Task_2(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
    
    while(1) {
        
        // 等待任务信号量
        OSTaskSemPend(0, OS_OPT_PEND_BLOCKING, 0, &err);
        GPIOC->ODR ^= GPIO_Pin_13;
    }
}
