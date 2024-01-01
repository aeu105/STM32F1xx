#include "bsp_uln2003.h"


/**
  * @brief  None
  * @param  None
  * @retval None
  */
void ULN2003_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// ULN2003 内部具有反向器
	GPIO_WriteBit(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, Bit_RESET);
}

/**
  * @brief  None
  * @param  None
  * @retval None
  */
// 一次 Stepper() 转动角度0.703125°	(5.625/8)°
// 调用 512次 Stepper() 转动角度 360°
void Stepper(unsigned int dir, unsigned int speed)
{
	if(0 == dir)
	{
		// 正向 A - AB - B - BC - C - CD - D - DA
		// A
		IN1_H; IN2_L; IN3_L; IN4_L; Delay_us(speed);
		// AB
		IN1_H; IN2_H; IN3_L; IN4_L; Delay_us(speed);
		// B
		IN1_L; IN2_H; IN3_L; IN4_L; Delay_us(speed);
		// BC
		IN1_L; IN2_H; IN3_H; IN4_L; Delay_us(speed);
		// C
		IN1_L; IN2_L; IN3_H; IN4_L; Delay_us(speed);
		// CD
		IN1_L; IN2_L; IN3_H; IN4_H; Delay_us(speed);
		// D
		IN1_L; IN2_L; IN3_L; IN4_H; Delay_us(speed);
		// DA
		IN1_H; IN2_L; IN3_L; IN4_H; Delay_us(speed);
	}
	else
	{
		// 反向 A - AD - D - DC - C - CB - B - BA
		// A
		IN1_H; IN2_L; IN3_L; IN4_L; Delay_us(speed);
		// AD
		IN1_H; IN2_L; IN3_L; IN4_H; Delay_us(speed);
		// D
		IN1_L; IN2_L; IN3_L; IN4_H; Delay_us(speed);
		// DC
		IN1_L; IN2_L; IN3_H; IN4_H; Delay_us(speed);
		// C
		IN1_L; IN2_L; IN3_H; IN4_L; Delay_us(speed);
		// CB
		IN1_L; IN2_H; IN3_H; IN4_L; Delay_us(speed);
		// B
		IN1_L; IN2_H; IN3_L; IN4_L; Delay_us(speed);
		// BA
		IN1_H; IN2_H; IN3_L; IN4_L; Delay_us(speed);
	}
}

void Angle_Control(unsigned int dir, double angle, unsigned int speed)
{
	unsigned int i;
	
	for(i = 0; i < (angle / STEPPER_ANGLE); i++)
	{
		Stepper(dir, speed);
	}
}
