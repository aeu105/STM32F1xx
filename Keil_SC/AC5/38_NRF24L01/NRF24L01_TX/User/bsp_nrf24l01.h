/*
	NRF24L01	<--->	STM32F103C8T6
	GND			<--->	GND
	VCC			<--->	3.3V
	CE			<--->	PB0
	CSN			<--->	PB1
	SCK			<--->	PA5
	MOSI		<--->	PA7
	MISO		<--->	PA6
	IRQ			<--->	PA4
*/

#ifndef __BSP_NRF24L01_H__
#define __BSP_NRF24L01_H__


#include <stm32f10x.h>


// NRF24L01相关命令的宏定义
#define	NRF_READ_REG	0x00	// Define read command to register
#define	NRF_WRITE_REG	0x20	// Define write command to register
#define	RD_RX_PLOAD		0x61	// Define RX payload register address
#define	WR_TX_PLOAD		0xA0	// Define TX payload register address
#define	FLUSH_TX		0xE1	// Define flush TX register command
#define	FLUSH_RX		0xE2	// Define flush RX register command
#define	REUSE_TX_PL		0xE3	// Define reuse TX payload register command
#define	NOP				0xFF	// Define No Operation, might be used to read status register

// NRF24L01相关寄存器地址的宏定义
#define	CONFIG		0x00	// 'Config' register address
#define	EN_AA		0x01	// 'Enable Auto Acknowledgment' register address
#define	EN_RXADDR	0x02	// 'Enabled RX addresses' register address
#define	SETUP_AW	0x03	// 'Setup address width' register address
#define	SETUP_RETR	0x04	// 'Setup Auto. Retrans' register address
#define	RF_CH		0x05	// 'RF channel' register address
#define	RF_SETUP	0x06	// 'RF setup' register address
#define	STATUS		0x07	// 'Status' register address
#define	OBSERVE_TX	0x08	// 'Observe TX' register address
#define	CD			0x09	// 'Carrier Detect' register address
#define	RX_ADDR_P0	0x0A	// 'RX address pipe0' register address
#define	RX_ADDR_P1	0x0B	// 'RX address pipe1' register address
#define	RX_ADDR_P2	0x0C	// 'RX address pipe2' register address
#define	RX_ADDR_P3	0x0D	// 'RX address pipe3' register address
#define	RX_ADDR_P4	0x0E	// 'RX address pipe4' register address
#define	RX_ADDR_P5	0x0F	// 'RX address pipe5' register address
#define	TX_ADDR		0x10	// 'TX address' register address
#define	RX_PW_P0	0x11	// 'RX payload width, pipe0' register address
#define	RX_PW_P1	0x12	// 'RX payload width, pipe1' register address
#define	RX_PW_P2	0x13	// 'RX payload width, pipe2' register address
#define	RX_PW_P3	0x14	// 'RX payload width, pipe3' register address
#define	RX_PW_P4	0x15	// 'RX payload width, pipe4' register address
#define	RX_PW_P5	0x16	// 'RX payload width, pipe5' register address
#define	FIFO_STATUS	0x17	// 'FIFO Status Register' register address


// PB1 -- CSN
#define NRF24L01_CSN_H GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET)
#define NRF24L01_CSN_L GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET)
// PB0 -- CE
#define NRF24L01_CE_H GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET)
#define NRF24L01_CE_L GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET)
// PA4 -- IRQ
#define NRF24L01_IRQ GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)


// 超时失败, 产生中断, MAX_RT 位会为 1
#define MAX_RT (1<<4)
// 发送完成, 产生中断, TX_DS 位会为 1
#define TX_DS (1<<5)
// 接收完成, 产生中断, RX_DR 位会为 1
#define RX_DR (1<<6)


void NRF24L01_Configuration(void);
unsigned int NRF24L01_Checking(void);

// 发送
void Set_NRF24L01_TX_Mode(void);
unsigned int NRF24L01_TxPacket(unsigned char *txbuf);

// 接收
void Set_NRF24L01_RX_Mode(void);
unsigned int NRF24L01_RxPacket(unsigned char *txbuf);


#endif	/* __BSP_NRF24L01_H__ */
