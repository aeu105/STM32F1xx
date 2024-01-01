#include "bsp_matrix_key.h"
#include "bsp_systick.h"


int Matrix_Key(void) {
	
	unsigned int Key, Val = 0;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// RCC 时钟开启在主函数中进行, 避免频繁开启
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// 引脚模式设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, Bit_RESET);	// 输出低电平
	
	if(0x0F != (GPIOA->IDR & 0x0F)) {	// 判断低 4 位状态
		
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
		
		// 行列翻转
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 上拉输入
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_WriteBit(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3, Bit_RESET);	// 输出低电平
		
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
		
		while((GPIOA->IDR & 0xF0) != 0xF0);	// 上升沿触发
		return Val;
	}
	else
		return 0;
}
