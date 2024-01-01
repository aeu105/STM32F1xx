#include "main.h"
#include "bsp_systick.h"
#include "bsp_lcd1602.h"


int main(void) {
	
	unsigned char Hex2char[] = "0123456789ABCDEF";
	
	unsigned int n = 0;
	unsigned int thounsand_bit, hunderd_bit, ten_bit, single_bit;
		
	SysTick_Configuration();
	
	LCD1602_GPIO_Configuration();
	LCD1602_Init();
	
	// 参数: 列位置(0~16)	行位置(0/1)	显示的内容
	LCD1602_Show_String(1, 0, (unsigned char *)"STM32 LCD1602\n");
	LCD1602_Show_String(2, 1, (unsigned char *)"Hello!\n");
	Delay_us(1000000);
	
	LCD1602_Clear_Screen();
	
	while(1) {
		
		thounsand_bit = n / 1000;
		hunderd_bit = (n % 1000) / 100;
		ten_bit = ((n % 1000) % 100) / 10;
		single_bit = n % 10;
		
		//LCD1602_Show_Char(15, 1, thounsand_bit + '0');	// 注意类型转换
		LCD1602_Show_Char(12, 1, Hex2char[thounsand_bit]);	// 千位
		LCD1602_Show_Char(13, 1, Hex2char[hunderd_bit]);	// 百位
		LCD1602_Show_Char(14, 1, Hex2char[single_bit]);	// 十位
		LCD1602_Show_Char(15, 1, Hex2char[ten_bit]);	// 个位
		n++;
		
		LCD1602_Write_Cmd(0x18);	// 显示的内容[整体]左移 1 格
		
		Delay_us(1000000);
	}
}
