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
		
		// 片选信号线置低位
		CS_LOW;
		
		// 读取数据
		Data = SPI1_Read();
		
		// 片选信号线置高
		CS_HIGH;
		
		// 数据处理
		// 读取 D2 值, 判断工作状态
		flag_D2 = Data & 0x0004;
		if(0 == flag_D2) {	// 工作正常
			
			// 读取 D14~D3 数据
			Data_Temp = Data << 1;
			Data_Temp = Data_Temp >> 4;
			
			Temperature = 1023.75 * (Data_Temp / 4095);
			
			printf("Temperature = %.2f\n", Temperature);
			Delay_us(100000);
		}
		else {	// 工作不正常
			
			printf("Sensor is borken!\n");
			Delay_us(100000);
		}
	}
}
