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
                
                // 任务消息队列发送给任务2
                OSTaskQPost(&Task2_TCB, "Hello!", sizeof("Hello!"), OS_OPT_POST_FIFO, &err);
            }
        }
        OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

void Task_2(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
    
    char *pMsg;
    OS_MSG_SIZE Msg_Size;
    
    while(1) {
        
        // 等待任务消息队列
        pMsg = OSTaskQPend(0, OS_OPT_PEND_BLOCKING, &Msg_Size, 0, &err);
        
        if(OS_ERR_NONE == err) {
            
            printf("%s, %d\n", pMsg, Msg_Size);
        }
    }
}
