#include "bsp_dma1.h"


unsigned char SendBuff[SENDBUFF_SIZE];


void DMA1_Configuration(void) {
	
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_DeInit(DMA1_Channel4);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;	// 0x40013804;	// 外设地址 USART1_DR	基地址 + 偏移地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SendBuff;	// 发送内容的地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	// 传输方向: 内存 -> 外设
	DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE; // 传输数据大小, 暂无单位
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	// 外设即数据[发送到的地址USART_DR]是否可变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	// 需发送的[数据地址SendBuff]是否可变
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;	//发送数据单位大小
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	// 接收数据单位大小
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	// 发送数据是否循环发送
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;	// 优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	// 失能内存到内存传输
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	
	DMA_ClearFlag(DMA1_FLAG_TC4);	// 清除 通道 4 传输完成标志位
}
