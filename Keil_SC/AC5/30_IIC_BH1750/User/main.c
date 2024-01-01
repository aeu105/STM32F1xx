#include "main.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_bh1750.h"


int main()
{
	unsigned int read_data;
	
	SysTick_Configuration();
	
	//USART1_Configuration();
	
	IIC1_Configuration();
	
	BH1750_Write_Cmd(POWER_ON_CMD);
	BH1750_Write_Cmd(RESET_CMD);
	BH1750_Write_Cmd(CON_HR_MODE1);
	Delay_us(1000000);
	
	while(1)
	{
		read_data = BH1750_Read_Result();
		
		printf("Lux = %f\n", read_data / 1.2);
		
		Delay_us(1000000);
	}
}
