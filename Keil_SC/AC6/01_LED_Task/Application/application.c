#include "application.h"


// ����Ӧ��, ���幦��ʵ��
void Led_Task(void *p_arg) {	// �ڲ�ѭ��ʵ�־��幦��
    
    OS_ERR err;
	
	(void)p_arg;
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        // OSTimeDly(1, OS_OPT_TIME_DLY, &err); // �˺�����ʱһ��ʱ�ӽ��� ms
        OSTimeDly(1000, OS_OPT_TIME_DLY, &err); // �����ʱ 1 s
	}
}
