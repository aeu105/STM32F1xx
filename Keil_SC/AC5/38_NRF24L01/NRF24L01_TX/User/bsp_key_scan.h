#ifndef __BSP_KEY_SCAN_H__
#define __BSP_KEY_SCAN_H__


#include <stm32f10x.h>


// 按键按下
#define KEY_ON 	1
// 按键未按下
#define KEY_OFF	0

void GPIOA_Configuration(void);
int Key_Scan(void);


#endif	/* __BSP_KEY_SCAN_H__ */
