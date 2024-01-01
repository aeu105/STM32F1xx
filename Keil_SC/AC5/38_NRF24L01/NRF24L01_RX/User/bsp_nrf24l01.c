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
	// ������ APB2 ���� ��� 72MHz ���з�Ƶ
	// ����Ƶ�����Ϊ 10Mbps
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
	
	// SPI ͨѶʱ��ͼ
	NRF24L01_CSN_L;
	
	// SPIͨѶ, д���Ҫ���ж�����
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

// ��� NRF24L01 �Ƿ�ͨѶ�ɹ�
// ���� 1 ʧ��
// ���� 0 �ɹ�
unsigned int NRF24L01_Checking(void) {
	
	unsigned char ch;
	
	NRF24L01_Write_Reg(NRF_WRITE_REG + TX_ADDR, 'A');	// д�Ĵ���(����+��ַ)
	ch = NRF24L01_Read_Reg(NRF_READ_REG + TX_ADDR);	// ���Ĵ���(����+��ַ)
	
	if(ch == 'A')
		return 0;	// ͨѶ�ɹ�
	else
		return 1;	// ͨѶʧ��
}

// ���÷���ģʽ
void Set_NRF24L01_TX_Mode(void) {
	
	NRF24L01_CE_L;
	
	NRF24L01_Write_Buf(NRF_WRITE_REG + TX_ADDR, TX_ADDRESS, 5);
	NRF24L01_Write_Reg(NRF_WRITE_REG + SETUP_RETR, 0x1A);
	NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0E);	// ����ģʽ
	
	NRF24L01_CE_H;
}

// ��������
unsigned int NRF24L01_TxPacket(unsigned char *txbuf) {
	
	unsigned char status;
	
	NRF24L01_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, RX_ADDRESS, 5);
	NRF24L01_Write_Buf(WR_TX_PLOAD, txbuf, 32);
	
	while(0 != NRF24L01_IRQ);
	
	status = NRF24L01_Read_Reg(NRF_READ_REG + STATUS);	// �˴�����ֵӦΪ 1
	
	NRF24L01_Write_Reg(NRF_WRITE_REG + STATUS, status);	// �������ж�ʱ, ��ǰλ���� 1, �Ե�ǰλ����д 1 ����, ������ж�
	
	
	if(status & MAX_RT) {	// ��ʱʧ���ж�, ��������ط�����
		
		// ���������
		NRF24L01_Write_Reg(FLUSH_TX, 0xFF);
		
		// ����ʧ��
		return 1;
	}
	
	if(status & TX_DS) {	// ������ɲ������ж�
		
		// ���ͳɹ�
		return 0;
	}
	
	return 1;
}

// ���ý���ģʽ
void Set_NRF24L01_RX_Mode(void) {
	
	NRF24L01_CE_L;
	
	NRF24L01_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, RX_ADDRESS, 5);
	NRF24L01_Write_Reg(NRF_WRITE_REG + RX_PW_P0, 32);
	NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0F);
	
	NRF24L01_CE_H;
}

// ��������
unsigned int NRF24L01_RxPacket(unsigned char *rxbuf) {
	
	unsigned char status;
	
	while(0 != NRF24L01_IRQ);
	
	status = NRF24L01_Read_Reg(NRF_READ_REG + STATUS);
	
	NRF24L01_Write_Reg(NRF_WRITE_REG + STATUS, status);
	
	if(status & RX_DR) {
		
		NRF24L01_Read_Buf(RD_RX_PLOAD, rxbuf, 32);
		// ���ճɹ�
		return 0;
	}
	
	return 1;
}
