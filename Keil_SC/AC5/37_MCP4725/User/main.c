#include "main.h"
#include "bsp_systick.h"
#include "bsp_mcp4725.h"


int main()
{
	SysTick_Configuration();
	
	IIC1_Configuration();
	
	MCP4725_SetOutPut_Voltage(3000);	// Êä³öµçÑ¹ 3V
	
	while(1)
	{
		//
	}
}
