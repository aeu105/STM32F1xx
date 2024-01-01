#include "application.h"


extern OS_SEM SEM;

unsigned char share_resource[30];

// ����Ӧ��, ���幦��ʵ��
void Task_1(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
    
    unsigned char Task1_str[] = "Hello world!";
	
    while(1) {
        
		OSSemPend(&SEM, 0, OS_OPT_PEND_BLOCKING, (CPU_TS *)0, &err);    // �����ź���
        
        printf("Task1:\n");
        memset(share_resource, 0, sizeof(share_resource));  // ���
        memcpy(share_resource, Task1_str, sizeof(Task1_str));
        //OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        printf("%s\n", share_resource);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        
        OSSemPost(&SEM, OS_OPT_POST_ALL, &err); // �����ź���
    }
}

void Task_2(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
	
    unsigned char Task2_str[] = "Good morning!";
    
    while(1) {
		
        OSSemPend(&SEM, 0, OS_OPT_PEND_BLOCKING, (CPU_TS *)0, &err);
        
        printf("Task2:\n");
        memset(share_resource, 0, sizeof(share_resource));
        memcpy(share_resource, Task2_str, sizeof(Task2_str));
        //OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        printf("%s\n", share_resource);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        
        OSSemPost(&SEM, OS_OPT_POST_ALL, &err);
    }
}
