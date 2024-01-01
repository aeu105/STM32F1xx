#ifndef __BSP_MCP4725_H__
#define __BSP_MCP4725_H__


#include <stm32f10x.h>
#include "bsp_iic.h"

#define VREF_5V 4920	// ²Î¿¼µçÑ¹ 4.92V

void MCP4725_SetOutPut_Voltage(unsigned int Vout);


#endif	/* __BSP_MCP4725_H__ */
