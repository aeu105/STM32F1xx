#include "application.h"

extern OS_MEM MemPartition;
extern unsigned char MyMemArray[3][20];

// 任务应用, 具体功能实现
void Task_1(void *p_arg) {
    
    OS_ERR err;
    
	(void)p_arg;
    
    char *pMsg;
    OS_MSG_SIZE Msg_Size;
    
    while(1) {
        
        pMsg = OSTaskQPend(0, OS_OPT_PEND_BLOCKING, &Msg_Size, 0, &err);
        
        if(0 == OS_ERR_NONE) {
            
            printf("%c, %d\n", *pMsg, Msg_Size);
        }
        
        OSMemPut(&MemPartition, pMsg, &err);
        //printf("%c, %d\n", *pMsg, Msg_Size);
    }
}
