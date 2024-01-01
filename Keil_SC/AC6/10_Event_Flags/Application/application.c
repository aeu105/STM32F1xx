#include "application.h"


extern OS_FLAG_GRP EventFlag;


// ����Ӧ��, ���幦��ʵ��
void Task_1(void *p_arg) {
    
    OS_ERR err;
	
	(void)p_arg;
	
    while(1) {
        
        if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
            
            GPIOC->ODR ^= GPIO_Pin_0;   // ����ָʾ����
            
            OSFlagPost( // �¼���־���0λ��1
                
                (OS_FLAG_GRP *)&EventFlag,
                (OS_FLAGS)0x01, // 0000 0001
                (OS_OPT)OS_OPT_POST_FLAG_SET,   // �� 0 λ��λ
                (OS_ERR *)&err
            );
        }
        if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)) {
            
            GPIOC->ODR ^= GPIO_Pin_1;   // ����ָʾ����
            
            OSFlagPost( // �¼���־���1λ��1
                
                (OS_FLAG_GRP *)&EventFlag,
                (OS_FLAGS)0x02, // 0000 0010
                (OS_OPT)OS_OPT_POST_FLAG_SET,   // �� 1 λ��λ
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
            (OS_TICK)0, // һֱ�ȴ�
            (OS_OPT)OS_OPT_PEND_FLAG_SET_ALL | OS_OPT_PEND_FLAG_CONSUME | OS_OPT_PEND_BLOCKING,   // ����λ����1 | ���ı�־λ | �����ȴ�
            (CPU_TS *)0,
            (OS_ERR *)&err
        );
        GPIOC->ODR ^= GPIO_Pin_2;   // �����¼������ȴ�, �ȴ���������ִ�д���
    }
}
