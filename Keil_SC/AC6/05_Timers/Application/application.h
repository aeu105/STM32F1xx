#ifndef __APPLICATION_H__
#define __APPLICATION_H__


#include "os.h"
#include "bsp_init.h"


void Led1_Task(void *p_arg);
void TmrCallback(OS_TMR *p_tmr, void *p_arg);


#endif	/* __APPLICATION_H__ */
