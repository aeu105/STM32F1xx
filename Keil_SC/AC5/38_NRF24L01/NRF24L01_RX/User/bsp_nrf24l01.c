#include "bsp_nrf24l01.h"


const unsigned char TX_ADDRESS[5] = {0x34, 0x43, 0x10, 0x10, 0x01};
const unsigned char RX_ADDRESS[5] = {0x34, 0x43, 0x10, 0x10, 0x01};

void NRF24L01_Configuration(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_SPI1, ENABLE);
	
	
	// PB0 -- CE, PB1 -- CSN
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// PA4 -- IRQ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// PA5 -- SCK, PA6 -- MISO, PA7 -- MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	// 挂载于 APB2 总线 需对 72MHz 进行分频
	// 工作频率最大为 10Mbps
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	
	SPI_Cmd(SPI1, ENABLE);
}

unsigned char SPI1_ReadWriteByte(unsigned char data) {
	
	while(RESET == SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI1, data);
	while(RESET == SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
	
	return SPI_I2S_ReceiveData(SPI1);
}

void NRF24L01_Write_Reg(unsigned char reg, unsigned char value) {
	
	// SPI 通讯时序图
	NRF24L01_CSN_L;
	
	// SPI通讯, 写完后要进行读操作
	SPI1_ReadWriteByte(reg);
	SPI1_ReadWriteByte(value);
	
	NRF24L01_CSN_H;
}

unsigned char NRF24L01_Read_Reg(unsigned char reg) {
	
	unsigned char reg_val;
	
	NRF24L01_CSN_L;
	
	SPI1_ReadWriteByte(reg);
	reg_val = SPI1_ReadWriteByte(0x00);
	
	NRF24L01_CSN_H;
	
	return reg_val;
}

void NRF24L01_Write_Buf(unsigned char reg, const unsigned char *pbuf, unsigned int len) {
	
	int i;
	
	NRF24L01_CSN_L;
	
	SPI1_ReadWriteByte(reg);
	
	for(i = 0; i < len; i++) {
		
		SPI1_ReadWriteByte(*pbuf++);
	}
	
	NRF24L01_CSN_H;
}

void NRF24L01_Read_Buf(unsigned char reg, unsigned char *pbuf, unsigned int len) {
	
	int i;
	
	NRF24L01_CSN_L;
	
	SPI1_ReadWriteByte(reg);
	
	for(i = 0; i < len; i++) {
		
		pbuf[i] = SPI1_ReadWriteByte(0x00);
	}
	
	NRF24L01_CSN_H;
}

// 检测 NRF24L01 是否通讯成功
// 返回 1 失败
// 返回 0 成功
unsigned int NRF24L01_Checking(void) {
	
	unsigned char ch;
	
	NRF24L01_Write_Reg(NRF_WRITE_REG + TX_ADDR, 'A');	// 写寄存器(命令+地址)
	ch = NRF24L01_Read_Reg(NRF_READ_REG + TX_ADDR);	// 读寄存器(命令+地址)
	
	if(ch == 'A')
		return 0;	// 通讯成功
	else
		return 1;	// 通讯失败
}

// 配置发送模式
void Set_NRF24L01_TX_Mode(void) {
	
	NRF24L01_CE_L;
	
	NRF24L01_Write_Buf(NRF_WRITE_REG + TX_ADDR, TX_ADDRESS, 5);
	NRF24L01_Write_Reg(NRF_WRITE_REG + SETUP_RETR, 0x1A);
	NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0E);	// 发送模式
	
	NRF24L01_CE_H;
}

// 发送数据
unsigned int NRF24L01_TxPacket(unsigned char *txbuf) {
	
	unsigned char status;
	
	NRF24L01_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, RX_ADDRESS, 5);
	NRF24L01_Write_Buf(WR_TX_PLOAD, txbuf, 32);
	
	while(0 != NRF24L01_IRQ);
	
	status = NRF24L01_Read_Reg(NRF_READ_REG + STATUS);	// 此处返回值应为 1
	
	NRF24L01_Write_Reg(NRF_WRITE_REG + STATUS, status);	// 当产生中断时, 当前位会置 1, 对当前位进行写 1 操作, 会清除中断
	
	
	if(status & MAX_RT) {	// 超时失败中断, 超过最大重发次数
		
		// 缓冲区清空
		NRF24L01_Write_Reg(FLUSH_TX, 0xFF);
		
		// 发送失败
		return 1;
	}
	
	if(status & TX_DS) {	// 发送完成产生的中断
		
		// 发送成功
		return 0;
	}
	
	return 1;
}

// 配置接收模式
void Set_NRF24L01_RX_Mode(void) {
	
	NRF24L01_CE_L;
	
	NRF24L01_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, RX_ADDRESS, 5);
	NRF24L01_Write_Reg(NRF_WRITE_REG + RX_PW_P0, 32);
	NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0F);
	
	NRF24L01_CE_H;
}

// 接收数据
unsigned int NRF24L01_RxPacket(unsigned char *rxbuf) {
	
	unsigned char status;
	
	while(0 != NRF24L01_IRQ);
	
	status = NRF24L01_Read_Reg(NRF_READ_REG + STATUS);
	
	NRF24L01_Write_Reg(NRF_WRITE_REG + STATUS, status);
	
	if(status & RX_DR) {
		
		NRF24L01_Read_Buf(RD_RX_PLOAD, rxbuf, 32);
		// 接收成功
		return 0;
	}
	
	return 1;
}
