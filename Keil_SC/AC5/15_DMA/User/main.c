#include "main.h"
#include "bsp_systick.h"
#include "bsp_gpio_configuration.h"
#include "bsp_usart1.h"
#include "bsp_dma1.h"


int main(void) {
	
	unsigned int i;
	
	SysTick_Configuration();
	
	GPIOC_Configuration();
	
	GPIOA_USATR1_Configuration(115200);
	
	DMA1_Configuration();
	
	
	printf("Start DMA transmission!\n");
	for(i = 50; i < SENDBUFF_SIZE; i++)
	{
		SendBuff[i] = i & 0xFF;
	}
	
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);	// ʹ�� USART1 �� [����] DMA ����
	// ע��������λ��
	DMA_Cmd(DMA1_Channel4, ENABLE);	// ʹ�� DMA1 ͨ�� 4
	
	printf("\nDMA transmission successful!\n");
	
	while (1) {
		
		Blinker();
	}
}
