#include "bsp_joystick.h"
#include "bsp_systick.h"
#include "bsp_usart.h"


void JoyStick_Configuration(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	// ADC1
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	// 单通道
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	// 由程序指定
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 2;
	ADC_Init(ADC1, &ADC_InitStructure);
	// 频率: 72 / 8 = 9 MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	ADC_Cmd(ADC1, ENABLE);
	
	// 校准
	ADC_ResetCalibration(ADC1);	// 重置指定的 ADC 的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));	// 获取 ADC 重置校准寄存器的状态, 若重置成功返回 RESET
	ADC_StartCalibration(ADC1);	// 开始指定 ADC 的校准
	while(ADC_GetCalibrationStatus(ADC1));	// 等待校准完成
}

u16 Get_ADC_Value(unsigned int channel) {	// 参数: 通道值
	
	// 采集一次时间: ((55.5 + 12.5) / 9) us = 7.5556 us
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_55Cycles5);	// Tconv = 55.5 + 12.5
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));	// 等待转换完成 (转换结束返回 1)
	return ADC_GetConversionValue(ADC1);	// 获取转换结果
}

void JoyStick_Scan(void) {
	
	u16 adc_x, adc_y;
	//float x, y;
	int x, y;
	
	// 数字量值
	adc_x = Get_ADC_Average(ADC_Channel_8, 10);
	adc_y = Get_ADC_Average(ADC_Channel_9, 10);
	
	if(KEY_ON == Key_Scan()) {
		
		printf("Key is pressed!\n");
	}
	
	/*
	printf("adc_x = %d\n", adc_x);
	printf("adc_y = %d\n", adc_y);
	printf("************\n");
	*/
	
	// 模拟量值
	x = adc_x * (3.3 / 4096);	// 取整
	y = adc_y * (3.3 / 4096);	// 取整
	
	/*
	printf("x = %lf\n", x);
	printf("y = %lf\n", y);
	printf("************\n");
	*/
	/*
	printf("x = %d\n", x);
	printf("y = %d\n", y);
	printf("************\n");
	*/
	
	if(x == 2 && y == 3)
		printf("Up!\n");
	else if(x == 2 && y == 0)
		printf("Down!\n");
	else if(x == 3 && y == 2)
		printf("Left!\n");
	else if(x == 0 && y == 2)
		printf("Right!\n");
	else if(x == 3 && y == 3)
		printf("Left_Up!\n");
	else if(x == 0 && y == 3)
		printf("Right_Up!\n");
	else if(x == 3 && y == 0)
		printf("Left_Down!\n");
	else if(x == 0 && y == 0)
		printf("Right_Down!\n");
	else
		printf("None!\n");
}

u16 Get_ADC_Average(unsigned int channel, unsigned int times) {
	
	int i;
	u16 total = 0;
	
	for(i = 0; i < times; i++) {
		
		total += Get_ADC_Value(channel);
		Delay_us(5000);
	}
	
	return (total / times);
}

int Key_Scan(void) {	// 按键 PB5 检测
	
	if(0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)) {
		
		Delay_us(10000);	// 延时 10ms
		if(0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)) {
			
			return KEY_ON;	// 按键按下, 返回 1
		}
		return KEY_OFF;
	}	
	return KEY_OFF;	
}
