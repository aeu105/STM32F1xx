## STM32基础教程

### IWDG 独立看门狗


时钟来源:

	LSI 频率 f(40 kHz) 进行 IWDG_PR(64) 分频


计数周期(约数值):

	t = (1 / (f / IWDG_PR)) = (1 / (40kHz / 64)) = 64 / 40kHz = 1.6 us
	

	T = nCount * t = 625 * 1.6 = 1000 us = 1 s

