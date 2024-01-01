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
	
	// ������ʼ�� -- PA0
	GPIOA_Configuration();
	
	NRF24L01_Configuration();
	
	// ��� NRF24L01 �Ƿ�ͨѶ�ɹ�
	while(NRF24L01_Checking()) {	// ���� 1 ʧ��
		
		printf("Connect to NRF24L01 Error!\n");
		Delay_us(1000000);
	}
	printf("Connert to NRF24L01 OK!\n");	// ���� 0 �ɹ�
	Delay_us(1000000);
	
	// ����ģ��Ϊ����ģʽ
	Set_NRF24L01_TX_Mode();
	
	while(1) {
		
		// ɨ�谴��״̬ PA0
		if(Key_Scan()) {	// ����ֵΪ 1, ��⵽��������
			
			while(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
			/*
			// ��������
			while(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
			// PC13 ��ת
			GPIOC->ODR ^= GPIO_Pin_13;
			*/
			
			// NRF24L01 ��ش���
			Control = 1;
			// ���Ͱ�������״̬
			while(0 != NRF24L01_TxPacket(&Control))
				printf("Send Failed!\n");
			
			Control = 1;
		}
		//LED_Blinker();
	}
}
