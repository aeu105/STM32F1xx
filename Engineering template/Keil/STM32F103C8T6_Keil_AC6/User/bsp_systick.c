#include "bsp_systick.h"


volatile unsigned long TimingDelay;


/**
  * @brief  None
  * @param  None
  * @retval None
  */
void SysTick_Configuration(void) {
	
	while(SysTick_Config(72));
	
	SysTick->CTRL &= ~(1<<0);
}

/**
  * @brief  None
  * @param  None
  * @retval None
  */
void Delay_us(unsigned long nCount) {
	
	TimingDelay = nCount;
	
	SysTick->CTRL |= (1<<0);
	
	while(TimingDelay);
	
	SysTick->CTRL &= ~(1<<0);
}
