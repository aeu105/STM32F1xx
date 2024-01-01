#include "bsp_tcs3200.h"


unsigned int amount;	// ����ֵ
unsigned int Red_Pulse, Green_Pulse, Blue_Pulse;	// �½�����ֵ
unsigned int Red_Ratio, Green_Ratio, Blue_Ratio;	// ��������


// PA0: S0	PA1: S1	PA2: S2	PA3: S3
void TCS3200_Configuration(unsigned int s0, unsigned int s1)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 100% Ƶ�����
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)s0);
	GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)s1);
}
// PA4: OUT
void PA4_EXTI4_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);	// ���� GPIOA �жϹ���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}
// ��ƽ��(��������)
void White_Balance(void)
{
	// ��ɫ S2: 0	S3: 0
	GPIO_WriteBit(GPIOA, GPIO_Pin_2 | GPIO_Pin_3, Bit_RESET);
	amount = 0;
	Delay_us(10000);	// ��λʱ�����½��ش���
	Red_Pulse = amount;
	Red_Ratio = 255 / Red_Pulse;	// ��������
	/*
	printf("Red_Pulse = %d\n", Red_Pulse);
	printf("Red_Ratio = %d\n", Red_Ratio);
	*/
	
	// ��ɫ	S2: 1	S3: 1
	GPIO_WriteBit(GPIOA, GPIO_Pin_2 | GPIO_Pin_3, Bit_SET);
	amount = 0;
	Delay_us(10000);	// ��λʱ�����½��ش���
	Green_Pulse = amount;
	Green_Ratio = 255 / Green_Pulse;	// ��������
	/*
	printf("Green_Pulse = %d\n", Green_Pulse);
	printf("Green_Ratio = %d\n", Green_Ratio);
	*/
	
	// ��ɫ	S2: 0	S3: 1
	GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
	amount = 0;
	Delay_us(10000);	// ��λʱ�����½��ش���
	Blue_Pulse = amount;
	Blue_Ratio = 255 / Blue_Pulse;	// ��������
	/*
	printf("Blue_Pulse = %d\n", Blue_Pulse);
	printf("Blue_Ratio = %d\n", Blue_Ratio);
	*/
	
	// �ر�
	GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET);
}

// ��ɫֵ
unsigned int TCS3200_Red(void)
{
	unsigned int Red_Value;	// Rֵ
	
	GPIO_WriteBit(GPIOA, GPIO_Pin_2 | GPIO_Pin_3, Bit_RESET);
	amount = 0;
	Delay_us(10000);	// ��λʱ�����½��ش���
	Red_Value = Red_Ratio * amount;
	
	if(Red_Value > 255)
		Red_Value = 255;
	
	return Red_Value;
}
// ��ɫֵ
unsigned int TCS3200_Green(void)
{
	unsigned int Green_Value;	// Gֵ
	
	GPIO_WriteBit(GPIOA, GPIO_Pin_2 | GPIO_Pin_3, Bit_SET);
	amount = 0;
	Delay_us(10000);	// ��λʱ�����½��ش���
	Green_Value = Green_Ratio * amount;
	
	if(Green_Value > 255)
		Green_Value = 255;
	
	return Green_Value;
}
// ��ɫֵ
unsigned int TCS3200_Blue(void)
{
	unsigned int Blue_Value;	// Bֵ
	
	GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
	amount = 0;
	Delay_us(10000);	// ��λʱ�����½��ش���
	Blue_Value = Blue_Value * amount;
	
	if(Blue_Value > 255)
		Blue_Value = 255;
	
	return Blue_Value;
}
