#include "bsp_spi.h"


void SPI1_Configuration(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
	
	// PA4	SPI1_NSS
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出, 片选
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// PA5	SPI1_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出, 时钟信号
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// PA6	SPI1_MISO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 浮空输入, 接收数据
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// PA7	SPI1_MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出, 发送数据
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// 数据模式: 单向/双向
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	// 主 SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;	// 数据帧结构: 16位/8位, 数据手册获取
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	// 时钟极性, SCK在空闲状态时为低电平, 根据外设决定
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	// 时钟相位, 数据线上信号在SCK时钟线的第二个跳变沿(偶数, 下降)被采样, 根据外设决定
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;	// 片选信号控制方式
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	// 波特率预分频值, 决定采集频率, 分频越小采集越快
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	// 数据传输从MSB(高位)/LSB(低位)开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	// 定义了用于CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);
	
	SPI_Cmd(SPI1, ENABLE);
}

u16 SPI1_Read(void) {
	
	// 等待发送缓冲区为空, 为空返回 SET
	while(RESET == SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
	
	// SPI通讯主机接收需要向从机发送数据(任意值)以开始通讯(从机不会主动开始发送数据)
	SPI_I2S_SendData(SPI1, 0x00);
	
	// 接收缓冲区非空开始接收, 非空返回 SET
	while(RESET == SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
	
	return SPI_I2S_ReceiveData(SPI1);
}
