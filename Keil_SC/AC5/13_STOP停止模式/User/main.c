#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_gpioa_exti0.h"


void Stop_Configuration(void);

int main(void) {
	
	unsigned int nCount;
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	PA0_EXTI0_Configuration();
	
	while(1) {
		
		for(nCount = 0; nCount < 10; nCount++) {
			
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
			Delay_us(200000);
			
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
			Delay_us(200000);
		}
		
		// 停止模式		唤醒后使用低速内部时钟 HSI
		Stop_Configuration();
		
		// 退出停止模式后需初始化 HSI / HSE 时钟, 此工作可在中断中进行
	}
}

/**
  * @brief  进入停止模式
  * @note   None
  * @param  None
  * @retval None
  */
void Stop_Configuration(void) {
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
}
