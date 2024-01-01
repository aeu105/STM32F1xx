#include "application.h"


extern OS_TCB Task2_TCB;

// ����Ӧ��, ���幦��ʵ��
void Task_1(void *p_arg) {
    
    OS_ERR err;
    
	(void)p_arg;
	
    while(1) {
        
        if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
            
            OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);
            if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
                
                // �����ź������͸�����2
                OSTaskSemPost(&Task2_TCB, OS_OPT_POST_NONE, &err);
            }
        }
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

void Task_2(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
    
    while(1) {
        
        // �ȴ������ź���
        OSTaskSemPend(0, OS_OPT_PEND_BLOCKING, 0, &err);
        GPIOC->ODR ^= GPIO_Pin_13;
    }
}
