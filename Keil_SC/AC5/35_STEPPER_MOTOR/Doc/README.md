# 步进电机


STM32	TB660
PA1		PUL+
PA2		DIR+
GND		ENA+	(上电电机锁住)




@1速度:
	频率
	

@2角度:
	脉冲个数
	

启停控制:(TIMx_CR1)

	定时器使能/失能
	
		TIM2->CR1 ^= 0x01;

方向:
	GPIOA->ODR ^= GPIO_Pin_2;