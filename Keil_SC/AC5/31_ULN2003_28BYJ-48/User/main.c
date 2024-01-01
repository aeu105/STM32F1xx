#include "main.h"
#include "bsp_systick.h"
#include "bsp_uln2003.h"


int main(void)
{
	SysTick_Configuration();
	
	ULN2003_Configuration();
	
	while(1)
	{
		Stepper(Pos, 1000);
		Angle_Control(Pos, 360, 1000);
	}
}
