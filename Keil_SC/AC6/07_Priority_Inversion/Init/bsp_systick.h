#ifndef __BSP_SYSTICK_H__
#define __BSP_SYSTICK_H__


#include <stm32f10x.h>
#include "os_cfg_app.h"


void SysTick_Configuration(void);
void Delay_us(unsigned long nCount);


#endif	/* __BSP_SYSTICK_H__ */
