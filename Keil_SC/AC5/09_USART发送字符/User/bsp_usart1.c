#include "bsp_usart1.h"


// PA9 TX / PA10 RX
void GPIOA_USATR1_Configuration(u32 BaudRate) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	// TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	// RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;	// USART 传输的波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	// 在一个帧中传输或者接收到的数据位数
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	// 定义发送的停止位数目
	USART_InitStructure.USART_Parity = USART_Parity_No;	// 奇偶失能
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 硬件流控失能
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	// 发送/接收使能
	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}
