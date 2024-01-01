#include "includes.h"


OS_TCB Task1_TCB;	// ������ƿ�
CPU_STK Task1_STK[128];	// ����ջ
OS_TCB Task2_TCB;
CPU_STK Task2_STK[128];


OS_SEM SEM; // �ź���
OS_Q MsgQ;  // ��Ϣ����
OS_PEND_DATA Mul_Pend_Array[2];


int main(void) {
	
	OS_ERR err;
	
	// ����Ӳ���ĳ�ʼ��
	Bsp_Init();
	
	/* ��ʼ��"uC/OS-III"�ں� */
	OSInit(&err);
    
    // �ź���
    OSSemCreate(
        
        (OS_SEM *)&SEM,
        (CPU_CHAR *)"SEM",
        (OS_SEM_CTR)0,
        (OS_ERR *)&err
    );
    // ��Ϣ����
    OSQCreate(
        
        (OS_Q *)&MsgQ,
        (CPU_CHAR *)"MsgQ",
        (OS_MSG_QTY)1000,
        (OS_ERR *)&err
    );
    Mul_Pend_Array[0].PendObjPtr = (OS_PEND_OBJ *)&SEM;
    Mul_Pend_Array[1].PendObjPtr = (OS_PEND_OBJ *)&MsgQ;
    
	// CreateTask ��������
	OSTaskCreate(
        
		(OS_TCB *)&Task1_TCB, (CPU_CHAR *)"Task_1",
		(OS_TASK_PTR)Task_1, (void *)0,
		(OS_PRIO)2, (CPU_STK *)&Task1_STK[0],
		(CPU_STK_SIZE)12, (CPU_STK_SIZE)128,
		(OS_MSG_QTY)0u, (OS_TICK)0u,
		(void *)0, (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR *)&err
	);
    OSTaskCreate(
        
		(OS_TCB *)&Task2_TCB, (CPU_CHAR *)"Task_2",
		(OS_TASK_PTR)Task_2, (void *)0,
		(OS_PRIO)2, (CPU_STK *)&Task2_STK[0],
		(CPU_STK_SIZE)12, (CPU_STK_SIZE)128,
		(OS_MSG_QTY)0u, (OS_TICK)0u,
		(void *)0, (OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR *)&err
	);
	/* ����������ϵͳ������Ȩ����uC/OS-III */
	OSStart(&err);
}
