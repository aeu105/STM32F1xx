#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_wwdg.h"


int main(void) {
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	
	// 上电(复位)时执行
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
	Delay_us(1000000);
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
	Delay_us(1000000);
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
	Delay_us(1000000);
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
	Delay_us(1000000);
	
	// 装载计数值, 上窗口值, 预分频值
	WWDG_Configuration(0x7F, 0x5F, WWDG_Prescaler_4);
	
	// @1非刷新区域: LED 间隔 1s 持续闪烁[复位]
	// 此处 [立即] 或 [延时<14563.556us] (从 0x7F(127) 减到 0x5F(95) 共减 32 个数, 用时约 14563.56us)进行喂狗操作, 将产生复位
//	Delay_us(14000);	// 延时数值 < 14563.556us
//	WWDG_SetCounter(WWDG_CNT);
	
	// @2刷新区域: LED 间隔 1s 闪烁 2 次后 0.5s 持续闪烁
	// 此处 [延时>14563.556us] 且 [延时<28672us] 进行喂狗操作, 延时>28672us时已进中断
	Delay_us(15000);	// 延时数值 > 14563.56us
	WWDG_SetCounter(WWDG_CNT);
	
	while(1) {
		
		// 进 WWDG 中断后若不执行喂狗操作则产生复位操作, 此处代码不执行
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		Delay_us(50000);
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		Delay_us(50000);
	}
}
