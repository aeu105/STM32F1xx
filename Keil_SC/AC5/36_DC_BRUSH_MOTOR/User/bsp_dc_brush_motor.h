#ifndef __BSP_DC_BRUSH_MOTOR_H__
#define __BSP_DC_BRUSH_MOTOR_H__


#include <stm32f10x.h>


#define AIN1_H	GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET)
#define AIN1_L	GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET)

#define AIN2_H	GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET)
#define AIN2_L	GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET)

#define STBY_H	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET)
#define STBY_L	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET)


void DC_Brush_Motor_Configuration(void);
void Encoder_Init_TIM4(void);
void TIM3_Base_Configuration(void);


#endif	/* __BSP_DC_BRUSH_MOTOR_H__ */
