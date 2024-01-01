#include "includes.h"


OS_TCB Task_LED_TCB;	// ������ƿ�
CPU_STK Task_LED_STK[128];	// ����ջ


int main(void) {
	
	OS_ERR err;
	
	// ����Ӳ���ĳ�ʼ��
	Bsp_Init();
	
	/* ��ʼ��"uC/OS-III"�ں� */
	OSInit(&err);
	
	// CreateTask ��������
	OSTaskCreate(
        
		(OS_TCB *)&Task_LED_TCB,	// �������OS_TCB�ĵ�ַ
		(CPU_CHAR *)"LED_Task",	// ��������
		(OS_TASK_PTR)Led_Task,	// ����������ʼ��ַ
		(void *)0,	// �����һ������ʱ���յ��Ĳ���
		(OS_PRIO)2,	// �������ȼ�
		(CPU_STK *)&Task_LED_STK[0],	// ����ջ�Ļ���ַ(����ַ����ջ�ռ����͵�ַ)
		(CPU_STK_SIZE)12,	// ����ջ����ȱ��(ջʣ��ռ�С�ڴ�ֵ�ᱨ��)
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
