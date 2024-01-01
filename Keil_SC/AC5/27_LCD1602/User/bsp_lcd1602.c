#include "bsp_lcd1602.h"


// IO 口配置
void LCD1602_GPIO_Configuration(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

// 初始化
void LCD1602_Init(void) {
	
	LCD1602_Write_Cmd(0x38);	// 2 行显示, 5*7 点阵, 数据总线 8 位
	LCD1602_Write_Cmd(0x0C);	// 开启显示, 关闭光标(无闪烁)
	LCD1602_Write_Cmd(0x06);	// 文字不动, 光标右移
	LCD1602_Write_Cmd(0x01);	// 清屏
}

// 写命令
void LCD1602_Write_Cmd(unsigned char cmd) {
	
	LCD1602_Wait_Ready();	// 确认显示屏状态: 忙/空闲
	
	LCD1602_RS_Clr();
	LCD1602_RW_Clr();
	
	// 设置各引脚状态, 写 0/1
	SET_LCD1602_D0((cmd >> 0) & 0x01);	// 写入的数据
	SET_LCD1602_D1((cmd >> 1) & 0x01);
	SET_LCD1602_D2((cmd >> 2) & 0x01);
	SET_LCD1602_D3((cmd >> 3) & 0x01);
	SET_LCD1602_D4((cmd >> 4) & 0x01);
	SET_LCD1602_D5((cmd >> 5) & 0x01);
	SET_LCD1602_D6((cmd >> 6) & 0x01);
	SET_LCD1602_D7((cmd >> 7) & 0x01);
	
	LCD1602_EN_Set();
	LCD1602_EN_Clr();	// 下降沿写入
}

// 等待准备就绪
void LCD1602_Wait_Ready(void) {
	
	GPIOC->CRH &= 0xFF0FFFFF;	// 清空 23~20 位数据
	GPIOC->CRH |= 4 << 20;	// GPIOC_13 改为浮空输入模式
	
	// 读状态的时序
	LCD1602_RS_Clr();
	LCD1602_RW_Set();
	LCD1602_EN_Set();
	Delay_us(5000);	// 用于稳定状态
	
	// 读引脚状态(1 表示状态忙)
	while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
	
	GPIOC->CRH &= 0xFF0FFFFF;
	GPIOC->CRH |= 3 << 20;	// LCD1602 就绪后, DB7 管脚改为输出
	
	LCD1602_EN_Clr();
}

// 写数据
void LCD1602_Write_Dat(unsigned char dat) {
	
	LCD1602_Wait_Ready();
	
	LCD1602_RS_Set();
	LCD1602_RW_Clr();
	
	SET_LCD1602_D0((dat >> 0) & 0x01);
	SET_LCD1602_D1((dat >> 1) & 0x01);
	SET_LCD1602_D2((dat >> 2) & 0x01);
	SET_LCD1602_D3((dat >> 3) & 0x01);
	SET_LCD1602_D4((dat >> 4) & 0x01);
	SET_LCD1602_D5((dat >> 5) & 0x01);
	SET_LCD1602_D6((dat >> 6) & 0x01);
	SET_LCD1602_D7((dat >> 7) & 0x01);
	
	LCD1602_EN_Set();
	LCD1602_EN_Clr();
}

// 清屏
void LCD1602_Clear_Screen(void) {
	
	LCD1602_Write_Cmd(0x01);
}

// 设置起始位置
void LCD1602_Set_Cursor(unsigned char x, unsigned char y) {
	
	unsigned char addr;	// 显示地址(位置)
	
	if(0 == y)
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	
	LCD1602_Write_Cmd(0x80 | addr);	// 设置地址
}

// 显示字符
void LCD1602_Show_Char(unsigned char x, unsigned char y, unsigned char dat) {
	
	LCD1602_Set_Cursor(x, y);	// 显示位置
	LCD1602_Write_Dat(dat);	// 显示内容
}

// 显示字符串
void LCD1602_Show_String(unsigned char x, unsigned char y, unsigned char *str) {
	
	LCD1602_Set_Cursor(x, y);
	
	while(*str)
		LCD1602_Write_Dat(*str++);
}
