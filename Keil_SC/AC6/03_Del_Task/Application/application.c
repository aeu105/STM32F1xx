#include "application.h"


extern OS_TCB Task_LED2_TCB;

// ����Ӧ��, ���幦��ʵ��
void Led1_Task(void *p_arg) {   // ����1 �� LED1 ��˸ 10 �κ�ɾ������ 2
    
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
            
            OSTaskSuspend(&Task_LED2_TCB, &err);    // ����2 ����
        }
        if(i == 10) {
            
            OSTaskResume(&Task_LED2_TCB, &err); // ����2 �ָ�
        }
        if(i == 15) {
            
            OSTaskDel(&Task_LED2_TCB, &err);    // ����2 ɾ��
        }
        if(i == 20) {
            
            OSTaskDel((OS_TCB *)0, &err);   // ������ָ��, ɾ����������
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
