#include "main.h"
#include "bsp_systick.h"
#include "bsp_led_configuration.h"
#include "bsp_usart.h"
#include "bsp_tim.h"
#include "bsp_hc_sr04.h"


int main(void) {
	
	// ����ֵ
	unsigned int nCount;
	float Distance = 0.0;
	
	SysTick_Configuration();
	
	//GPIO_Configuration();
	
	GPIOA_USART1_Configuration(115200);
	
	TIM2_BaseConfiguration();
	
	GPIOB_SR04_Configuration();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	while(1) {
		
		//Blinker();
		
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET);
		Delay_us(15);	// ��ʱ���� 10us
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);
		
		TIM_Cmd(TIM2, ENABLE);
		
		// Trig ���� 8 �� 40KHz �����, Echo ����ߵ�ƽ, �ߵ�ƽʱ��������������
		// ��� Echo ����ߵ�ƽ��ʼ����(����������Ϊ�ߵ�ƽ)
		while(RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7));
		// ������ʱ��, �����ֵ 0
		TIM_SetCounter(TIM2, 0);
		// �ȴ���ƽΪ��
		while(SET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7));
		// �رն�ʱ��, ����ʱ��ֵ
		TIM_Cmd(TIM2, DISABLE);
		
		nCount = TIM_GetCounter(TIM2);
		
		// 340 m/s * (nCount us / 1000000) = (340 m/s * (nCount / 1000000) s) m = ((340 m/s * (nCount / 1000000) s) * 100) cm
		// ��λ: cm
		Distance = (((340 * (nCount / 1000000)) * 100) / 2);
		
		printf("Distance = %.2f cm\n", Distance);
		Delay_us(1000000);
	}
}
