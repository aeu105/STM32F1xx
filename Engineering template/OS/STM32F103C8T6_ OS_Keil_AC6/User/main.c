#include "includes.h"


OS_TCB Task_TCB;	// 任务控制块 Task_TCB
CPU_STK Task_STK[128];	// 任务栈 Task_STK[128]


int main(void) {
	
	OS_ERR err;
	
	// 板载硬件的初始化
	Bsp_Init();
	
	/* 初始化"uC/OS-III"内核 */
	OSInit(&err);
	
	// CreateTask 创建任务
	OSTaskCreate(
		(OS_TCB *)&Task_TCB,	// 任务控制OS_TCB的地址 &Task_TCB
		(CPU_CHAR *)"Task",	// 任务名称 "Task"
		(OS_TASK_PTR)Task,	// 任务代码的起始地址 Task
		(void *)0,	// 任务第一次运行时接收到的参数
		(OS_PRIO)2,	// 任务优先级
		(CPU_STK *)&Task_STK[0],	// 任务栈的基地址(基地址总是栈空间的最低地址) &Task_STK[0]
		(CPU_STK_SIZE)12,	// 任务栈的深度标记(栈剩余空间小于此值会报警)
		(CPU_STK_SIZE)128,	// 任务栈的大小
		(OS_MSG_QTY)0u,	// 任务内部消息队列的大小
		(OS_TICK)0u,	// 时间片轮转的长度
		(void *)0,	// 用户补充的存储区
		(OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	// 任务特定选项
		(OS_ERR *)&err	// 错误码
	);
	
	/* 启动多任务系统，控制权交给uC/OS-III */
	OSStart(&err);
}
