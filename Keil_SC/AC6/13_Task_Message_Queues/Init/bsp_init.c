#include "bsp_init.h"


// Ӳ�������ʼ��

void Bsp_Init(void) {
	
	// ʱ�ӳ�ʼ��, 1ms ��һ���ж�
	SysTick_Configuration();
    
    // LED ��ʼ��
    Led_Configuration();
    
    // USART ��ʼ��
    USART_Configuration(115200);
}
