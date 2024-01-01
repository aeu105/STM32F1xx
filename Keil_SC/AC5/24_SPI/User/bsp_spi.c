#include "bsp_spi.h"


void SPI1_Configuration(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
	
	// PA4	SPI1_NSS
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// ͨ���������, Ƭѡ
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// PA5	SPI1_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// �����������, ʱ���ź�
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// PA6	SPI1_MISO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// ��������, ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// PA7	SPI1_MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// �����������, ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// ����ģʽ: ����/˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	// �� SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;	// ����֡�ṹ: 16λ/8λ, �����ֲ��ȡ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	// ʱ�Ӽ���, SCK�ڿ���״̬ʱΪ�͵�ƽ, �����������
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	// ʱ����λ, ���������ź���SCKʱ���ߵĵڶ���������(ż��, �½�)������, �����������
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;	// Ƭѡ�źſ��Ʒ�ʽ
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	// ������Ԥ��Ƶֵ, �����ɼ�Ƶ��, ��ƵԽС�ɼ�Խ��
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	// ���ݴ����MSB(��λ)/LSB(��λ)��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	// ����������CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);
	
	SPI_Cmd(SPI1, ENABLE);
}

u16 SPI1_Read(void) {
	
	// �ȴ����ͻ�����Ϊ��, Ϊ�շ��� SET
	while(RESET == SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
	
	// SPIͨѶ����������Ҫ��ӻ���������(����ֵ)�Կ�ʼͨѶ(�ӻ�����������ʼ��������)
	SPI_I2S_SendData(SPI1, 0x00);
	
	// ���ջ������ǿտ�ʼ����, �ǿշ��� SET
	while(RESET == SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
	
	return SPI_I2S_ReceiveData(SPI1);
}
