#include "bsp_matrix_key.h"
#include "bsp_systick.h"


int Matrix_Key(void) {
	
	unsigned int Key, Val = 0;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// RCC ʱ�ӿ������������н���, ����Ƶ������
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// ����ģʽ����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// ͨ���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, Bit_RESET);	// ����͵�ƽ
	
	if(0x0F != (GPIOA->IDR & 0x0F)) {	// �жϵ� 4 λ״̬
		
		Delay_us(200);
		
		Key = (GPIOA->IDR & 0x0F);
		
		if(0x0F != Key) {
			
			switch(Key) {
				
				case 0x0E: Val = 1; break;
				case 0x0D: Val = 5; break;
				case 0x0B: Val = 9; break;
				case 0x07: Val = 13; break;
				default: break;
			}
		}
		else
			return 0;
		
		// ���з�ת
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// ͨ���������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// ��������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_WriteBit(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3, Bit_RESET);	// ����͵�ƽ
		
		if(0xF0 != (GPIOA->IDR & 0xF0)) {
			
			Delay_us(200);
			
			Key = (GPIOA->IDR & 0xF0);
			
			if(0xF0 != Key) {
				
				switch(Key) {
					
					case 0xE0: Val += 0; break;
					case 0xD0: Val += 1; break;
					case 0xB0: Val += 2; break;
					case 0x70: Val += 3; break;
					default: break;
				}
			}
			else
				return 0;
		}
		else
			return 0;
		
		while((GPIOA->IDR & 0xF0) != 0xF0);	// �����ش���
		return Val;
	}
	else
		return 0;
}
