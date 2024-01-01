#include "application.h"


OS_TMR tmr1;

// ����Ӧ��, ���幦��ʵ��
void Led1_Task(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
	
    OSTmrCreate((OS_TMR *)&tmr1,
                (CPU_CHAR *)"tmr1",
                (OS_TICK)30,    // 50 * 100ms = 5s, �״ζ�ʱ��Ϊ��
                (OS_TICK)1,    // 1 * 100ms = 0.1s, �����¼�� 0.1s ����һ�λص�����
                (OS_OPT)OS_OPT_TMR_PERIODIC,
                (OS_TMR_CALLBACK_PTR)TmrCallback,
                (void *)0,
                (OS_ERR *)&err
    );
    
    while(1) {
		
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) {
            
            OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_DLY, &err);
            
            if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) {
            
                OSTmrStart(&tmr1, &err);
            }
        }
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0) {
            
            OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_DLY, &err);
            
            if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0) {
            
                OSTmrStop(&tmr1, OS_OPT_TMR_NONE, (void *)0, &err);
            }
        }
        
        OSTimeDlyHMSM(0, 0, 3, 0, OS_OPT_TIME_DLY, &err);
    }
}

void TmrCallback(OS_TMR *p_tmr, void *p_arg) {
    
    GPIOC->ODR ^= GPIO_Pin_13;
}
