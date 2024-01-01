#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_usart.h"
#include "bsp_nrf24l01.h"
#include "bsp_key_scan.h"


int main(void) {
	
	unsigned char Control = 0;
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	
	USART_Configuration(115200);
	
	// 按键初始化 -- PA0
	GPIOA_Configuration();
	
	NRF24L01_Configuration();
	
	// 检测 NRF24L01 是否通讯成功
	while(NRF24L01_Checking()) {	// 返回 1 失败
		
		printf("Connect to NRF24L01 Error!\n");
		Delay_us(1000000);
	}
	printf("Connert to NRF24L01 OK!\n");	// 返回 0 成功
	Delay_us(1000000);
	
	// 配置模块为发送模式
	Set_NRF24L01_TX_Mode();
	
	while(1) {
		
		// 扫描按键状态 PA0
		if(Key_Scan()) {	// 返回值为 1, 检测到按键按下
			
			while(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
			/*
			// 按键测试
			while(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
			// PC13 反转
			GPIOC->ODR ^= GPIO_Pin_13;
			*/
			
			// NRF24L01 相关代码
			Control = 1;
			// 发送按键按下状态
			while(0 != NRF24L01_TxPacket(&Control))
				printf("Send Failed!\n");
			
			Control = 1;
		}
		//LED_Blinker();
	}
}
