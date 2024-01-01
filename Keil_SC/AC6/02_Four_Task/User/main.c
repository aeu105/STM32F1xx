#include "includes.h"


OS_TCB Task_LED1_TCB;	// ������ƿ�
CPU_STK Task_LED1_STK[128];	// ����ջ
OS_TCB Task_LED2_TCB;
CPU_STK Task_LED2_STK[128];
OS_TCB Task_LED3_TCB;
CPU_STK Task_LED3_STK[128];
OS_TCB Task_LED4_TCB;
CPU_STK Task_LED4_STK[128];


int main(void) {
	
	OS_ERR err;
	
	// ����Ӳ���ĳ�ʼ��
	Bsp_Init();
	
	/* ��ʼ��"uC/OS-III"�ں� */
	OSInit(&err);
	
	// CreateTask ��������
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
	
	/* ����������ϵͳ������Ȩ����uC/OS-III */
	OSStart(&err);
}
