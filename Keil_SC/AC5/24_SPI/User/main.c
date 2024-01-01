#include "main.h"
#include "bsp_systick.h"
#include "bsp_led_configuration.h"
#include "bsp_usart.h"
#include "bsp_spi.h"


int main(void) {
	
	u16 Data, Data_Temp;
	float Temperature;
	
	unsigned int flag_D2;
	
	SysTick_Configuration();
	
	LED_Configuration();
	
	GPIOA_USART1_Configuration();
	
	SPI1_Configuration();
	
	while(1) {
		
		Blinker();
		
		// Ƭѡ�ź����õ�λ
		CS_LOW;
		
		// ��ȡ����
		Data = SPI1_Read();
		
		// Ƭѡ�ź����ø�
		CS_HIGH;
		
		// ���ݴ���
		// ��ȡ D2 ֵ, �жϹ���״̬
		flag_D2 = Data & 0x0004;
		if(0 == flag_D2) {	// ��������
			
			// ��ȡ D14~D3 ����
			Data_Temp = Data << 1;
			Data_Temp = Data_Temp >> 4;
			
			Temperature = 1023.75 * (Data_Temp / 4095);
			
			printf("Temperature = %.2f\n", Temperature);
			Delay_us(100000);
		}
		else {	// ����������
			
			printf("Sensor is borken!\n");
			Delay_us(100000);
		}
	}
}
