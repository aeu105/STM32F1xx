#include "application.h"


extern OS_SEM SEM; // 信号量
extern OS_Q MsgQ;  // 消息队列
extern OS_PEND_DATA Mul_Pend_Array[2];


// 任务应用, 具体功能实现
void Task_1(void *p_arg) {
    
    OS_ERR err;
    OS_TMR Tmr;
	
	(void)p_arg;
    
    // 软件定时器
    OSTmrCreate(
    
        (OS_TMR *)&Tmr,
        (CPU_CHAR *)"Tmr",
        (OS_TICK)0,
        (OS_TICK)1, // 100ms
        (OS_OPT)OS_OPT_TMR_PERIODIC,
        (OS_TMR_CALLBACK_PTR)TmrCallBack,
        (void *)0,
        (OS_ERR *)&err
    );
    OSTmrStart(&Tmr, &err);
	
    while(1) {
        
        OSQPost(
            
            (OS_Q *)&MsgQ,
            (void *)"Hello!",
            (OS_MSG_SIZE)sizeof("Hello!"),
            (OS_OPT)OS_OPT_POST_FIFO | OS_OPT_POST_ALL,
            (OS_ERR *)&err
        );
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

void Task_2(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
    
    while(1) {
        
        OSPendMulti(
            
            (OS_PEND_DATA *)Mul_Pend_Array,
            (OS_OBJ_QTY)2,
            (OS_TICK)0,
            (OS_OPT)OS_OPT_PEND_BLOCKING,
            (OS_ERR *)&err
        );
        
        if(Mul_Pend_Array[0].RdyObjPtr == Mul_Pend_Array[0].PendObjPtr) {
            
            printf("Key is pressed\n");
        }
        if(Mul_Pend_Array[1].RdyObjPtr == Mul_Pend_Array[1].PendObjPtr) {
            
            printf("Received: %s, Size: %d bytes.\n", (char *)Mul_Pend_Array[1].RdyMsgPtr, Mul_Pend_Array[1].RdyMsgSize);
        }
    }
}

void TmrCallBack(OS_TMR *p_tmr, void *p_arg) {
    
    OS_ERR err;
    
    if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
        
        OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);
        if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
            
            OSSemPost(&SEM, OS_OPT_POST_ALL, &err);
        }
    }
}
