#include "includes.h"


// 优先级定义
#define High_Task_PRIO      11
#define Middle_Task_PRIO    12
#define Low_Task_PRIO       13


OS_TCB Task1_TCB;	// 任务控制块
CPU_STK Task1_STK[128];	// 任务栈
OS_TCB Task2_TCB;
CPU_STK Task2_STK[128];
OS_TCB Task3_TCB;
CPU_STK Task3_STK[128];


// OS_SEM SEM;  // 信号量
OS_MUTEX MUTEX;   // 互斥信号量

int main(void) {
	
	OS_ERR err;
	
	// 板载硬件的初始化
	Bsp_Init();
	
	/* 初始化"uC/OS-III"内核 */
	OSInit(&err);
    
    /*
    // 信号量创建
    OSSemCreate(
        (OS_SEM *)&SEM,
        (CPU_CHAR *)"SEM",
        (OS_SEM_CTR)1,  // 信号量初始值
        (OS_ERR *)err
    );
    */
    // 互斥信号量创建
    OSMutexCreate((OS_MUTEX *)&MUTEX, (CPU_CHAR *)"MUTEX", (OS_ERR *)&err);
    
    
	// CreateTask 创建任务
	OSTaskCreate(
        
		(OS_TCB *)&Task1_TCB, (CPU_CHAR *)"Task_1",
		(OS_TASK_PTR)Task_1, (void *)0,
		(OS_PRIO)High_Task_PRIO, (CPU_STK *)&Task1_STK[0],
		(CPU_STK_SIZE)12, (CPU_STK_SIZE)128,
		(OS_MSG_QTY)0u, (OS_TICK)0u,
		(void *)0, (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR *)&err
	);
    OSTaskCreate(
        
		(OS_TCB *)&Task2_TCB, (CPU_CHAR *)"Task_2",
		(OS_TASK_PTR)Task_2, (void *)0,
		(OS_PRIO)Middle_Task_PRIO, (CPU_STK *)&Task2_STK[0],
		(CPU_STK_SIZE)12, (CPU_STK_SIZE)128,
		(OS_MSG_QTY)0u, (OS_TICK)0u,
		(void *)0, (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR *)&err
	);
    OSTaskCreate(
        
		(OS_TCB *)&Task3_TCB, (CPU_CHAR *)"Task_3",
		(OS_TASK_PTR)Task_3, (void *)0,
		(OS_PRIO)Low_Task_PRIO, (CPU_STK *)&Task3_STK[0],
		(CPU_STK_SIZE)12, (CPU_STK_SIZE)128,
		(OS_MSG_QTY)0u, (OS_TICK)0u,
		(void *)0, (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR *)&err
	);
	/* 启动多任务系统，控制权交给uC/OS-III */
	OSStart(&err);
}
