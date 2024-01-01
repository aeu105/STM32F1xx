#include "application.h"


extern OS_TCB Task2_TCB;
extern OS_MEM MemPartition;
extern unsigned char MyMemArray[3][20];

// ����Ӧ��, ���幦��ʵ��
void Task_1(void *p_arg) {
    
    OS_ERR err;
    
	(void)p_arg;
    
    unsigned int nCount = 0;
    char *p_Mem_Blk;
	
    while(1) {
        
        // ����
        p_Mem_Blk = OSMemGet(&MemPartition, &err);
        sprintf(p_Mem_Blk, "%d", nCount++);
        
        if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
            
            OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);
            if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
                
                // ������Ϣ���з��͸�����2
                OSTaskQPost(&Task2_TCB, p_Mem_Blk, strlen(p_Mem_Blk), OS_OPT_POST_FIFO, &err);
            }
        }
        OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);
        
        // �ͷ�
        OSMemPut(&MemPartition, p_Mem_Blk, &err);
    }
}

void Task_2(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
    
    char *pMsg;
    OS_MSG_SIZE Msg_Size;
    
    while(1) {
        
        // �ȴ�������Ϣ����
        pMsg = OSTaskQPend(0, OS_OPT_PEND_BLOCKING, &Msg_Size, 0, &err);
        
        if(OS_ERR_NONE == err) {
            
            printf("%s, %d\n", pMsg, Msg_Size);
        }
    }
}
