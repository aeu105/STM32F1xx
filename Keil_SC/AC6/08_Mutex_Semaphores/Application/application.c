#include "application.h"


// extern OS_SEM SEM;
extern OS_MUTEX MUTEX;


// 任务应用, 具体功能实现
void Task_1(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
	
    while(1) {
        
        OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
        
        //OSSemPend(&SEM, 0, OS_OPT_PEND_BLOCKING, (CPU_TS *)0, &err);
        OSMutexPend(&MUTEX, 0, OS_OPT_PEND_BLOCKING, (CPU_TS *)0, &err);
        
        printf("High_Task Running!\n");
        
        //OSSemPost(&SEM, OS_OPT_POST_ALL, &err);
        OSMutexPost(&MUTEX, OS_OPT_POST_ALL, &err);
        
        OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

void Task_2(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
    
    while(1) {
        
        printf("Middle_Task Running!\n");
        
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}


void Task_3(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
    
    unsigned int times;
    
    while(1) {
        
        //OSSemPend(&SEM, 0, OS_OPT_PEND_BLOCKING, (CPU_TS *)0, &err);
        OSMutexPend(&MUTEX, 0, OS_OPT_PEND_BLOCKING, (CPU_TS *)0, &err);
        printf("Low_Task Running!\n");
        
        for(times = 0; times < 2000000; times++) {
            
            OSSched();
        }
        
        //OSSemPost(&SEM, OS_OPT_POST_ALL, &err);
        OSMutexPost(&MUTEX, OS_OPT_POST_ALL, &err);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}
