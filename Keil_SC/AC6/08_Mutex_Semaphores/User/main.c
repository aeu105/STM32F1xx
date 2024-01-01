#include "includes.h"


// ���ȼ�����
#define High_Task_PRIO      11
#define Middle_Task_PRIO    12
#define Low_Task_PRIO       13


OS_TCB Task1_TCB;	// ������ƿ�
CPU_STK Task1_STK[128];	// ����ջ
OS_TCB Task2_TCB;
CPU_STK Task2_STK[128];
OS_TCB Task3_TCB;
CPU_STK Task3_STK[128];


// OS_SEM SEM;  // �ź���
OS_MUTEX MUTEX;   // �����ź���

int main(void) {
	
	OS_ERR err;
	
	// ����Ӳ���ĳ�ʼ��
	Bsp_Init();
	
	/* ��ʼ��"uC/OS-III"�ں� */
	OSInit(&err);
    
    /*
    // �ź�������
    OSSemCreate(
        (OS_SEM *)&SEM,
        (CPU_CHAR *)"SEM",
        (OS_SEM_CTR)1,  // �ź�����ʼֵ
        (OS_ERR *)err
    );
    */
    // �����ź�������
    OSMutexCreate((OS_MUTEX *)&MUTEX, (CPU_CHAR *)"MUTEX", (OS_ERR *)&err);
    
    
	// CreateTask ��������
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
	/* ����������ϵͳ������Ȩ����uC/OS-III */
	OSStart(&err);
}
