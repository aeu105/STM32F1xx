#include "bsp_lcd1602.h"


// IO ������
void LCD1602_GPIO_Configuration(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// ͨ���������
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

// ��ʼ��
void LCD1602_Init(void) {
	
	LCD1602_Write_Cmd(0x38);	// 2 ����ʾ, 5*7 ����, �������� 8 λ
	LCD1602_Write_Cmd(0x0C);	// ������ʾ, �رչ��(����˸)
	LCD1602_Write_Cmd(0x06);	// ���ֲ���, �������
	LCD1602_Write_Cmd(0x01);	// ����
}

// д����
void LCD1602_Write_Cmd(unsigned char cmd) {
	
	LCD1602_Wait_Ready();	// ȷ����ʾ��״̬: æ/����
	
	LCD1602_RS_Clr();
	LCD1602_RW_Clr();
	
	// ���ø�����״̬, д 0/1
	SET_LCD1602_D0((cmd >> 0) & 0x01);	// д�������
	SET_LCD1602_D1((cmd >> 1) & 0x01);
	SET_LCD1602_D2((cmd >> 2) & 0x01);
	SET_LCD1602_D3((cmd >> 3) & 0x01);
	SET_LCD1602_D4((cmd >> 4) & 0x01);
	SET_LCD1602_D5((cmd >> 5) & 0x01);
	SET_LCD1602_D6((cmd >> 6) & 0x01);
	SET_LCD1602_D7((cmd >> 7) & 0x01);
	
	LCD1602_EN_Set();
	LCD1602_EN_Clr();	// �½���д��
}

// �ȴ�׼������
void LCD1602_Wait_Ready(void) {
	
	GPIOC->CRH &= 0xFF0FFFFF;	// ��� 23~20 λ����
	GPIOC->CRH |= 4 << 20;	// GPIOC_13 ��Ϊ��������ģʽ
	
	// ��״̬��ʱ��
	LCD1602_RS_Clr();
	LCD1602_RW_Set();
	LCD1602_EN_Set();
	Delay_us(5000);	// �����ȶ�״̬
	
	// ������״̬(1 ��ʾ״̬æ)
	while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
	
	GPIOC->CRH &= 0xFF0FFFFF;
	GPIOC->CRH |= 3 << 20;	// LCD1602 ������, DB7 �ܽŸ�Ϊ���
	
	LCD1602_EN_Clr();
}

// д����
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

// ����
void LCD1602_Clear_Screen(void) {
	
	LCD1602_Write_Cmd(0x01);
}

// ������ʼλ��
void LCD1602_Set_Cursor(unsigned char x, unsigned char y) {
	
	unsigned char addr;	// ��ʾ��ַ(λ��)
	
	if(0 == y)
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	
	LCD1602_Write_Cmd(0x80 | addr);	// ���õ�ַ
}

// ��ʾ�ַ�
void LCD1602_Show_Char(unsigned char x, unsigned char y, unsigned char dat) {
	
	LCD1602_Set_Cursor(x, y);	// ��ʾλ��
	LCD1602_Write_Dat(dat);	// ��ʾ����
}

// ��ʾ�ַ���
void LCD1602_Show_String(unsigned char x, unsigned char y, unsigned char *str) {
	
	LCD1602_Set_Cursor(x, y);
	
	while(*str)
		LCD1602_Write_Dat(*str++);
}
