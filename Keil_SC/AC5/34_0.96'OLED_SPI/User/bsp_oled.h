#ifndef __BSP_OLED_H__
#define __BSP_OLED_H__


#include <stm32f10x.h>
#include "bsp_systick.h"


// OLED端口配置
#define OLED_SCLK_Set()	GPIO_SetBits(GPIOA, GPIO_Pin_6)
#define OLED_SCLK_Clr()	GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define OLED_SDIN_Set()	GPIO_SetBits(GPIOA, GPIO_Pin_7)
#define OLED_SDIN_Clr()	GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define OLED_RST_Set()	GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define OLED_RST_Clr()	GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define OLED_DC_Set()	GPIO_SetBits(GPIOA, GPIO_Pin_9)
#define OLED_DC_Clr()	GPIO_ResetBits(GPIOA, GPIO_Pin_9)
#define OLED_CS_Set()	GPIO_SetBits(GPIOA, GPIO_Pin_10)
#define OLED_CS_Clr()	GPIO_ResetBits(GPIOA, GPIO_Pin_10)


#define OLED_CMD	0	// 写命令
#define OLED_DATA	1	// 写数据

void OLED_Init(void);
void OLED_WR_Byte(unsigned char dat, unsigned int cmd);
void OLED_Clear(void);
// x: 列(列低地址/列高地址)	y: page页的编号(0~7/0~8)
void OLED_Set_Pos(unsigned int x, unsigned int y);
// y0~y1: 0~7	x0~x1: 0~127
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char bmp[]);
void OLED_Set(void);

#endif	/* __BSP_OLED_H__ */
