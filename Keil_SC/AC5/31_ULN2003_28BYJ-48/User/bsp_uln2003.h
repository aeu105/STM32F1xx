#ifndef __BSP_ULN2003_H__
#define __BSP_ULN2003_H__


#include <stm32f10x.h>
#include "bsp_systick.h"

// PA4
#define IN1_H	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET)
#define IN1_L	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET)
// PA5
#define IN2_H	GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET)
#define IN2_L	GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET)
// PA6
#define IN3_H	GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET)
#define IN3_L	GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_RESET)
// PA7
#define IN4_H	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET)
#define IN4_L	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_RESET)

#define STEPPER_ANGLE	0.703125	// (5.625 / 8)

// 方向
enum dir{Pos, Neg};	// Pos = 0 正向， Neg = 1 反向

void ULN2003_Configuration(void);
void Stepper(unsigned int dir, unsigned int speed);
void Angle_Control(unsigned int dir, double angle, unsigned int speed);

#endif	/* __BSP_ULN2003_H__ */
