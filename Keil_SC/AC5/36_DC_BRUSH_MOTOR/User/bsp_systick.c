#include "bsp_systick.h"


unsigned long TimingDelay;

void SysTick_Configuration(void)
{
	while(SysTick_Config(72));
	SysTick->CTRL &= ~(1<<0);
}

void Delay_us(unsigned long nCount)
{
	TimingDelay = nCount;
	SysTick->CTRL |= (1<<0);
	while(TimingDelay);
	SysTick->CTRL &= ~(1<<0);
}
