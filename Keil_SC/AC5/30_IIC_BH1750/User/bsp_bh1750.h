#ifndef __BSP_BH1750_H__
#define __BSP_BH1750_H__


#include <stm32f10x.h>
#include "bsp_iic.h"

#define BH1750_ADDR		0x46
#define POWER_ON_CMD	0x01
#define RESET_CMD		0x07
#define CON_HR_MODE1	0x10
#define CON_HR_MODE2	0x11


void BH1750_Write_Cmd(unsigned char cmd);
unsigned int BH1750_Read_Result(void);

#endif	/* __BSP_BH1750_H__ */
