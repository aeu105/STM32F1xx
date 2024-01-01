#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_usart1.h"
#include "bsp_rtc.h"

int main(void) {
	
	unsigned int flag;
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	
	GPIOA_USATR1_Configuration(115200);
	
	flag = RTC_Configuration();
	
	if(flag == 0)	// 未配置过 RTC, 需要设置当前时间
		Set_Time();
	
	while(1) {
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		Delay_us(50000);
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		Delay_us(1000000);
		
		Time_Display(RTC_GetCounter());
	}
}
