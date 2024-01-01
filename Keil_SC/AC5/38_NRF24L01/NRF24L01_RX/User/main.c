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
	
	// ��� NRF24L01 �Ƿ�ͨѶ�ɹ�
	while(NRF24L01_Checking()) {	// ���� 1 ʧ��
		
		printf("Connect to NRF24L01 Error!\n");
		Delay_us(1000000);
	}
	printf("Connert to NRF24L01 OK!\n");	// ���� 0 �ɹ�
	Delay_us(1000000);
	
	// ����ģ��Ϊ����ģʽ
	Set_NRF24L01_RX_Mode();
	
	while(1) {
		
		//LED_Blinker();
		// ��������, �ı� LED ״̬
		while(0 != NRF24L01_RxPacket(&Rec));
		
		if(1 == Rec)
			GPIOC->ODR ^= GPIO_Pin_13;
	}
}
