#include "main.h"
#include "bsp_systick.h"
#include "bsp_digital_tube.h"
#include "bsp_tim2.h"


unsigned int Num_Count = 0;

int main(void) {
	
	//unsigned int i;
	
	SysTick_Configuration();
	
	Digital_Tube_Configuration();
	
	_74HC595_Configuration();
	
	TIM2_BaseConfiguration();
	
	_74HC595_Send_Data(num[2], 3);	// �� 4 ���������ʾ���� 2
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	while(1) {
		
		// �����������ʾ
		/*
		for(i = 0; i < 12; i++) {
			
			GPIOA->ODR = num[i];
			Delay_us(500000);
		}
		*/
		
		Digital_Tube_74HC595_Dispaly(Num_Count);
		
		// ���ö�ʱ�� ��ʱ/����
		//Count++;
		//Delay_us(1000000);
	}
}
