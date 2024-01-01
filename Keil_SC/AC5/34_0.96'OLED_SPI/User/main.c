#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_oled.h"
#include "bmp.h"

#define TIME 500000

int main(void) {
	
	unsigned int nCount = 0;
	unsigned int hundred_bit, ten_bit, one_bit;
	
	SysTick_Configuration();
	
	OLED_Init();
	
	// 哔哩哔哩
	OLED_DrawBMP(0, 0, 15, 1, bilibili[0]);
	OLED_DrawBMP(16, 0, 31, 1, bilibili[1]);
	OLED_DrawBMP(32, 0, 47, 1, bilibili[2]);
	OLED_DrawBMP(48, 0, 63, 1, bilibili[3]);
	
	// 王鹏宇
	OLED_DrawBMP(81, 0, 96, 1, Slogan[0]);
	OLED_DrawBMP(97, 0, 112, 1, Slogan[1]);
	OLED_DrawBMP(113, 0, 128, 1, Slogan[2]);
	
	while(1) {
		
		hundred_bit = nCount / 100;
		ten_bit = (nCount % 100) / 10;
		one_bit = nCount % 10;
		
		// 起始坐标, 结束坐标, 数组
		OLED_DrawBMP(39, 4, 54, 7, number[hundred_bit]);
		OLED_DrawBMP(56, 4, 71, 7, number[ten_bit]);
		OLED_DrawBMP(73, 4, 88, 7, number[one_bit]);
		Delay_us(1000000);
		nCount++;
		
		if(nCount == 999)
			nCount = 0;
	}
}
