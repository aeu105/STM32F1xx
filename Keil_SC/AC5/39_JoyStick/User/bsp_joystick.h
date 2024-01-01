/*
	JoyStick				STM32F103C8T6
	
	GDN			<--->		GND
	5V			<--->		5V
	VRX			<--->		PB0
	VRY			<--->		PB1
	SW			<--->		PB5
*/

#ifndef __BSP_JOYSTICK_H__
#define __BSP_JOYSTICK_H__


#include <stm32f10x.h>


// 按键按下
#define KEY_ON 	1
// 按键未按下
#define KEY_OFF	0

void JoyStick_Configuration(void);
void JoyStick_Scan(void);
u16 Get_ADC_Average(unsigned int channel, unsigned int times);
int Key_Scan(void);


#endif	/* __BSP_JOYSTICK_H__ */
