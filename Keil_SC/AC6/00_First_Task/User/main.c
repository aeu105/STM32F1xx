#include "includes.h"


OS_TCB Task_TCB;	// ������ƿ� Task_TCB
CPU_STK Task_STK[128];	// ����ջ Task_STK[128]


int main(void) {
	
	OS_ERR err;
	
	/* ��ʼ��"uC/OS-III"�ں� */
	OSInit(&err);
	
	// CreateTask ��������
	OSTaskCreate(
        
		(OS_TCB *)&Task_TCB,	// �������OS_TCB�ĵ�ַ &Task_TCB
		(CPU_CHAR *)"MyFirst_Task",	// �������� "Task"
		(OS_TASK_PTR)Task,	// ����������ʼ��ַ Task
		(void *)0,	// �����һ������ʱ���յ��Ĳ���
		(OS_PRIO)2,	// �������ȼ� 2~61
		(CPU_STK *)&Task_STK[0],	// ����ջ�Ļ���ַ(����ַ����ջ�ռ����͵�ַ) &Task_STK[0]
		(CPU_STK_SIZE)12,	// ����ջ����ȱ��(ջʣ��ռ�С�ڴ�ֵ�ᱨ��) ~< 10%
		(CPU_STK_SIZE)128,	// ����ջ�Ĵ�С
		(OS_MSG_QTY)0u,	// �����ڲ���Ϣ���еĴ�С(��״̬��������Ϣ)
		(OS_TICK)0u,	// ʱ��Ƭ��ת�ĳ���
		(void *)0,	// �û�����Ĵ洢��
		(OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	// �����ض�ѡ��
		(OS_ERR *)&err	// ������
	);
	
	/* ����������ϵͳ������Ȩ����uC/OS-III */
	OSStart(&err);
}
