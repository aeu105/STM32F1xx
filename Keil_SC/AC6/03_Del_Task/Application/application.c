#include "application.h"


extern OS_TCB Task_LED2_TCB;

// 任务应用, 具体功能实现
void Led1_Task(void *p_arg) {   // 任务1 的 LED1 闪烁 10 次后删除任务 2
    
    unsigned int i = 0;
    
    OS_ERR err;
	
	(void)p_arg;
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        
        i++;
        if(i == 5) {
            
            OSTaskSuspend(&Task_LED2_TCB, &err);    // 任务2 挂起
        }
        if(i == 10) {
            
            OSTaskResume(&Task_LED2_TCB, &err); // 任务2 恢复
        }
        if(i == 15) {
            
            OSTaskDel(&Task_LED2_TCB, &err);    // 任务2 删除
        }
        if(i == 20) {
            
            OSTaskDel((OS_TCB *)0, &err);   // 参数空指针, 删除任务自身
        }
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
