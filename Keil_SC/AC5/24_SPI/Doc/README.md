#SPI

根据SPI时钟极性(CPOL)和时钟相位(CPHA)位置的不同, 分为四种SPI模式:

@1
	CPOL = 0, SCK在空闲状态时为低电平;
	CPOL = 1, SCK在空闲状态时为高电平.

@2
	CPHA = 0, MOSI或MISO数据线上的信号将会在SCK时钟线的第一个跳变沿(奇数, 上升或下降)被采样;
	CPHA = 1, 数据线上信号在SCK时钟线的第二个跳变沿(偶数, 上升或下降)被采样.

注:
	时钟极性是指SPI通讯设备处于空闲状态时(也可以认为这是SPI通讯开始时, 即CS线为低电平时), SCK信号线的电平信号.
	
	时钟相位是指数据的采样时刻.



STM32F103C8T6
PA4	<-->	SPI1_NSS
PA5	<-->	SPI1_SCK
PA6	<-->	SPI1_MISO
PA7	<-->	SPI1_MOSI

