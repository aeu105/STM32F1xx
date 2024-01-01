#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_iwdg.h"


int main(void) {
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	
	IWDG_Configuration();
	
	// 此段仅在上电(复位)时执行
	// @1 LED闪烁
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
	Delay_us(500000);	// 延时 500ms
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
	Delay_us(400000);	// 延时 400ms
	
	// 以上 MCU 启动后 900ms 进入 while() 循环体, 此时间 < 1s, 不产生 IWDG 复位
	while(1) {
		
		IWDG_ReloadCounter();	// IWDG 重装载值
		// @2
		Delay_us(900000);	// 进入循环体后重装载值, IWDG不产生复位,
							// 此处延时 900ms < 1s 后进行重装载, 不产生 IWDG 复位, LED常灭
	}
}
