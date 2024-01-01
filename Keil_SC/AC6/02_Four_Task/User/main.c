#include "includes.h"


OS_TCB Task_LED1_TCB;	// 任务控制块
CPU_STK Task_LED1_STK[128];	// 任务栈
OS_TCB Task_LED2_TCB;
CPU_STK Task_LED2_STK[128];
OS_TCB Task_LED3_TCB;
CPU_STK Task_LED3_STK[128];
OS_TCB Task_LED4_TCB;
CPU_STK Task_LED4_STK[128];


int main(void) {
	
	OS_ERR err;
	
	// 板载硬件的初始化
	Bsp_Init();
	
	/* 初始化"uC/OS-III"内核 */
	OSInit(&err);
	
	// CreateTask 创建任务
	OSTaskCreate(
        
		(OS_TCB *)&Task_LED1_TCB, (CPU_CHAR *)"LED1_Task",
		(OS_TASK_PTR)Led1_Task, (void *)0,
		(OS_PRIO)2, (CPU_STK *)&Task_LED1_STK[0],
		(CPU_STK_SIZE)12, (CPU_STK_SIZE)128,
		(OS_MSG_QTY)0u, (OS_TICK)0u,
		(void *)0, (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR *)&err
	);
        
    OSTaskCreate(
        
		(OS_TCB *)&Task_LED2_TCB, (CPU_CHAR *)"LED2_Task",
		(OS_TASK_PTR)Led2_Task, (void *)0,
		(OS_PRIO)3, (CPU_STK *)&Task_LED2_STK[0],
		(CPU_STK_SIZE)12, (CPU_STK_SIZE)128,
		(OS_MSG_QTY)0u, (OS_TICK)0u,
		(void *)0, (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR *)&err
	);
        
    OSTaskCreate(
        
		(OS_TCB *)&Task_LED3_TCB, (CPU_CHAR *)"LED3_Task",
		(OS_TASK_PTR)Led3_Task, (void *)0,
		(OS_PRIO)4, (CPU_STK *)&Task_LED3_STK[0],
		(CPU_STK_SIZE)12, (CPU_STK_SIZE)128,
		(OS_MSG_QTY)0u, (OS_TICK)0u,
		(void *)0, (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR *)&err
	);
        
    OSTaskCreate(
        
		(OS_TCB *)&Task_LED4_TCB, (CPU_CHAR *)"LED4_Task",
		(OS_TASK_PTR)Led4_Task, (void *)0,
		(OS_PRIO)5, (CPU_STK *)&Task_LED4_STK[0],
		(CPU_STK_SIZE)12, (CPU_STK_SIZE)128,
		(OS_MSG_QTY)0u, (OS_TICK)0u,
		(void *)0, (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR *)&err
	);
	
	/* 启动多任务系统，控制权交给uC/OS-III */
	OSStart(&err);
}
