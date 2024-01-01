#include "main.h"
#include "bsp_systick.h"
#include "bsp_led_configuration.h"
#include "bsp_usart.h"
#include "bsp_tim.h"
#include "bsp_hc_sr04.h"


int main(void) {
	
	// 计数值
	unsigned int nCount;
	float Distance = 0.0;
	
	SysTick_Configuration();
	
	//GPIO_Configuration();
	
	GPIOA_USART1_Configuration(115200);
	
	TIM2_BaseConfiguration();
	
	GPIOB_SR04_Configuration();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	while(1) {
		
		//Blinker();
		
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET);
		Delay_us(15);	// 延时至少 10us
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);
		
		TIM_Cmd(TIM2, ENABLE);
		
		// Trig 发出 8 个 40KHz 脉冲后, Echo 输出高电平, 高电平时间与检测距离成正比
		// 检测 Echo 输出高电平后开始计数(即引脚输入为高电平)
		while(RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7));
		// 开启定时器, 并设初值 0
		TIM_SetCounter(TIM2, 0);
		// 等待电平为低
		while(SET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7));
		// 关闭定时器, 读定时器值
		TIM_Cmd(TIM2, DISABLE);
		
		nCount = TIM_GetCounter(TIM2);
		
		// 340 m/s * (nCount us / 1000000) = (340 m/s * (nCount / 1000000) s) m = ((340 m/s * (nCount / 1000000) s) * 100) cm
		// 单位: cm
		Distance = (((340 * (nCount / 1000000)) * 100) / 2);
		
		printf("Distance = %.2f cm\n", Distance);
		Delay_us(1000000);
	}
}
