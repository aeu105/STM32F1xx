#ifndef __BSP_KEY_SCAN_H__
#define __BSP_KEY_SCAN_H__


#include <stm32f10x.h>


// ��������
#define KEY_ON 	1
// ����δ����
#define KEY_OFF	0

void GPIOA_Configuration(void);
int Key_Scan(void);


#endif	/* __BSP_KEY_SCAN_H__ */
