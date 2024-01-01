#include "main.h"
#include "bsp_systick.h"
#include "bsp_stepper_motor.h"


int main(void)
{
	//unsigned int speed_rpm = 1;
	SysTick_Configuration();
	
	Dir_Configuration();
	// 转向控制
	MOTOR_DIR_POS;	
	
	STEPPER_MOTOR_Configuration();
	TIM4_CNT_Configuration();
	
	// 初始周期值
	//Set_Speed_RPM(speed_rpm);
	
	while(1)
	{
		Pulse_Output(10, 2000);	// 10 转/分钟, 转 90°
		// 利用按键控制速度
		/*
		// 任意按键扫描
		if(Key1)
		{
			// 注意取值范围判断 < 100
			Set_Speed_RPM(++speed_rpm);
		}
		if(Key2)
		{
			// 注意取值范围判断 > 0
			Set_Speed_RPM(--speed_rpm);
		}
		*/
	}
}
