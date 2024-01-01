#ifndef __BSP_LCD1602_H__
#define __BSP_LCD1602_H__


#define LCD1602_RS_Set()	GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define LCD1602_RS_Clr()	GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define LCD1602_RW_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define LCD1602_RW_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define LCD1602_EN_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define LCD1602_EN_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_13)

#define SET_LCD1602_D0(a)	GPIO_WriteBit(GPIOB, GPIO_Pin_14, (BitAction)(a))
#define SET_LCD1602_D1(a)	GPIO_WriteBit(GPIOB, GPIO_Pin_15, (BitAction)(a))
#define SET_LCD1602_D2(a)	GPIO_WriteBit(GPIOA, GPIO_Pin_9, (BitAction)(a))
#define SET_LCD1602_D3(a)	GPIO_WriteBit(GPIOA, GPIO_Pin_10, (BitAction)(a))
#define SET_LCD1602_D4(a)	GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)(a))
#define SET_LCD1602_D5(a)	GPIO_WriteBit(GPIOA, GPIO_Pin_12, (BitAction)(a))
#define SET_LCD1602_D6(a)	GPIO_WriteBit(GPIOB, GPIO_Pin_5, (BitAction)(a))
#define SET_LCD1602_D7(a)	GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(a))


#include <stm32f10x.h>
#include "bsp_systick.h"


void LCD1602_GPIO_Configuration(void);
void LCD1602_Init(void);
void LCD1602_Write_Cmd(unsigned char cmd);
void LCD1602_Wait_Ready(void);
void LCD1602_Clear_Screen(void);
void LCD1602_Show_String(unsigned char x, unsigned char y, unsigned char *str);
void LCD1602_Show_Char(unsigned char x, unsigned char y, unsigned char dat);


#endif	/* __BSP_LCD1602_H__ */
