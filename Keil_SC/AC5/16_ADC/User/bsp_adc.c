#include "bsp_adc.h"
#include "bsp_systick.h"

uint16_t ADC_ConvertVal;

// 利用 DMA
void ADC1_Configuration(void) {
	
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (0x40012400 + 0x4c);	// ADC1_DR	0X4001 2400 + 0x4c
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertVal;	// 发送内容的地址 转换结果为 12 位分辨率
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	// 外设 -> 内存
	DMA_InitStructure.DMA_BufferSize = 1; // 传输数据大小, 暂无单位
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	// 外设即数据[发送到的地址USART_DR]是否可变
	DMA_InitStructure.DMA_MemoryInc = DMA_PeripheralInc_Disable;	// 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_HalfWord;	//发送数据单位大小
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	// 接收数据单位大小
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	// 发送数据是否循环发送
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;	// 优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	// 使能内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// 转换由软件触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	// 数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);	// 需要 < 14 MHz
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_55Cycles5);	// 转换一次用时: 周期 12.5 + 55.5 = 68
																					// 频率 72 / 8 = 9 MHz
																					// 时间 t = 68 * (1 / 9 MHz) = 7.556e-6 s =  7.556 us
	ADC_TempSensorVrefintCmd(ENABLE);	// 使能温度传感器和内部参考电压通道
	ADC_DMACmd(ADC1, ENABLE);
	
	ADC_Cmd(ADC1, ENABLE);
	
	// ADC 自校准
	ADC_ResetCalibration(ADC1);	// 重置 ADC 的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));	// 获取校准寄存器的状态, 等待重置完成， 返回 0 重置成功
	ADC_StartCalibration(ADC1);	// 开始校准
	while(ADC_GetCalibrationStatus(ADC1));	// 等待校准完成， 返回 0 校准完成
	
	// 使能软件转换启动功能(触发转换)
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
