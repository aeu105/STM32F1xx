#include "main.h"
#include "bsp_systick.h"
#include "bsp_stepper_motor.h"


int main(void)
{
	//unsigned int speed_rpm = 1;
	SysTick_Configuration();
	
	Dir_Configuration();
	// ת�����
	MOTOR_DIR_POS;	
	
	STEPPER_MOTOR_Configuration();
	TIM4_CNT_Configuration();
	
	// ��ʼ����ֵ
	//Set_Speed_RPM(speed_rpm);
	
	while(1)
	{
		Pulse_Output(10, 2000);	// 10 ת/����, ת 90��
		// ���ð��������ٶ�
		/*
		// ���ⰴ��ɨ��
		if(Key1)
		{
			// ע��ȡֵ��Χ�ж� < 100
			Set_Speed_RPM(++speed_rpm);
		}
		if(Key2)
		{
			// ע��ȡֵ��Χ�ж� > 0
			Set_Speed_RPM(--speed_rpm);
		}
		*/
	}
}
