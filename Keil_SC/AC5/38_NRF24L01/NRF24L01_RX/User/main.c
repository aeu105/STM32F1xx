#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_usart.h"
#include "bsp_nrf24l01.h"


int main(void) {
	
	unsigned char Rec;
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	
	USART_Configuration(115200);
	
	NRF24L01_Configuration();
	
	// 检测 NRF24L01 是否通讯成功
	while(NRF24L01_Checking()) {	// 返回 1 失败
		
		printf("Connect to NRF24L01 Error!\n");
		Delay_us(1000000);
	}
	printf("Connert to NRF24L01 OK!\n");	// 返回 0 成功
	Delay_us(1000000);
	
	// 配置模块为接收模式
	Set_NRF24L01_RX_Mode();
	
	while(1) {
		
		//LED_Blinker();
		// 接收数据, 改变 LED 状态
		while(0 != NRF24L01_RxPacket(&Rec));
		
		if(1 == Rec)
			GPIOC->ODR ^= GPIO_Pin_13;
	}
}
