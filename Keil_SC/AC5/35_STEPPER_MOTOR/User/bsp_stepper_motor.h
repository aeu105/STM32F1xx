#ifndef __BSP_STEPPER_MOTOR_H__
#define __BSP_STEPPER_MOTOR_H__


#include <stm32f10x.h>
#include "bsp_systick.h"


#define MOTOR_DIR_POS	GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET)
#define MOTOR_DIR_NEG	GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET)

void STEPPER_MOTOR_Configuration(void);
void Dir_Configuration(void);
void Set_Speed_RPM(unsigned int speed);
void TIM4_CNT_Configuration(void);
void Pulse_Output(unsigned int rpm, unsigned int Pulsenum);


#endif	/* __BSP_STEPPER_MOTOR_H__ */
