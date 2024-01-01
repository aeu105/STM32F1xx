#include "main.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_tcs3200.h"


int main()
{
	unsigned int R = 0, G = 0, B = 0;
	unsigned int i;
	
	SysTick_Configuration();
	
	USART1_Configuration();
	
	TCS3200_Configuration(1, 1);	// S0: 1	S1: 1	100%Ƶ�����
	PA4_EXTI4_Configuration();	// PA4: OUT	�ⲿ�жϹ���, ���ڼ���������ŵ�λʱ�����½��ش���
	
	printf("First White Balance.\n");
	for(i = 10; i > 0; i--)	// ��ƽ��׼��ʱ��
	{
		printf("Start White Balance after %d s\n", i);
		Delay_us(1000000);
	}
	// �ȴ���ƽ��
	printf("White_Balance...\n");
	
	White_Balance();	// ��ƽ��
	Delay_us(500000);	// ��Ϊ��ʱ
	
	printf("White_Balance succeed!\n");
	Delay_us(500000);
	
	printf("Start to detect colour:\n");
	for(i = 0; i >= 1; i--)
	{
		printf("Count = %d\n", i);
		Delay_us(1000000);
	}
	
	while(1)
	{
		R = TCS3200_Red();
		G = TCS3200_Green();
		B = TCS3200_Blue();
		/*
		printf("R = %d\n", R);
		printf("G = %d\n", G);
		printf("B = %d\n", B);
		printf("=====================\n");
		Delay_us(1000000);
		*/
		if(R > G && R > B)
			printf("Red\n");
		else if(G > R && G > B)
			printf("Green\n");
		else if(B > R && B > G)
			printf("Blue\n");
		else
			printf("Error!\n");
		printf("================");
		Delay_us(1000000);
	}
}
