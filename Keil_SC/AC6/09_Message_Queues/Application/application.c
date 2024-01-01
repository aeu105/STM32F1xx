#include "application.h"


extern OS_Q MsgQ;

// 任务应用, 具体功能实现
void Task_1(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
	
    while(1) {
        
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) {
            
            OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);
            if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) {
                
                //while(0 != GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
                    
                    // 消息队列发送消息
                    OSQPost(
                        (OS_Q *)&MsgQ,
                        (void *)"Hello!",
                        (OS_MSG_SIZE)sizeof("Hello!"),
                        (OS_OPT)OS_OPT_POST_FIFO | OS_OPT_POST_ALL,
                        (OS_ERR *)&err
                    );
                    printf("Task1 send message to queue.\n");
                //}
            }
        }
        //OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

void Task_2(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
    
    char *pMsg;
    OS_MSG_SIZE MsgQ_Size;
    
    while(1) {
        
        // 消息队列接收消息
        pMsg = OSQPend((OS_Q *)&MsgQ,
                       (OS_TICK)0,
                       (OS_OPT)OS_OPT_PEND_BLOCKING,
                       (OS_MSG_SIZE *)&MsgQ_Size,
                       (CPU_TS *)0,
                       (OS_ERR *)&err
        );
        
        if(err == OS_ERR_NONE) {
            
            printf("Task2 reveied from MsgQ: %s, size: %d\n", pMsg, MsgQ_Size);
        }
    }
}
