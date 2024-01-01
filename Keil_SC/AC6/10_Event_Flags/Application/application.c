#include "application.h"


extern OS_FLAG_GRP EventFlag;


// 任务应用, 具体功能实现
void Task_1(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
	
    while(1) {
        
        if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
            
            GPIOC->ODR ^= GPIO_Pin_0;   // 按键指示作用
            
            OSFlagPost( // 事件标志组第0位置1
                
                (OS_FLAG_GRP *)&EventFlag,
                (OS_FLAGS)0x01, // 0000 0001
                (OS_OPT)OS_OPT_POST_FLAG_SET,   // 第 0 位置位
                (OS_ERR *)&err
            );
        }
        if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) {
            
            GPIOC->ODR ^= GPIO_Pin_1;   // 按键指示作用
            
            OSFlagPost( // 事件标志组第1位置1
                
                (OS_FLAG_GRP *)&EventFlag,
                (OS_FLAGS)0x02, // 0000 0010
                (OS_OPT)OS_OPT_POST_FLAG_SET,   // 第 1 位置位
                (OS_ERR *)&err
            );
        }
        OSTimeDlyHMSM(0, 0, 0, 20, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

void Task_2(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
    
    while(1) {
        
        OSFlagPend(
            
            (OS_FLAG_GRP *)&EventFlag,
            (OS_FLAGS)0x03, // 0000 0011
            (OS_TICK)0, // 一直等待
            (OS_OPT)OS_OPT_PEND_FLAG_SET_ALL | OS_OPT_PEND_FLAG_CONSUME | OS_OPT_PEND_BLOCKING,   // 所有位均置1 | 消耗标志位 | 阻塞等待
            (CPU_TS *)0,
            (OS_ERR *)&err
        );
        GPIOC->ODR ^= GPIO_Pin_2;   // 上面事件阻塞等待, 等待不到不会执行此行
    }
}
