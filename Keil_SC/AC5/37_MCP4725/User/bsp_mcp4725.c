#include "bsp_mcp4725.h"


// 输出电压值单位 mV
void MCP4725_SetOutPut_Voltage(unsigned int Vout)
{
	unsigned int Dn;
	char Dn_H, Dn_L;
	
	Dn = (Vout * 4096) / VREF_5V;
	// 中文手册P24
	Dn_H = (0x0F00 & Dn) >> 8;
	Dn_L = (0x00FF & Dn);
	
	IIC_START();
	IIC_Send_Byte(0xC0);	// 器件代码: 1100	地址位A2, A1, A0: 000	1100+000+0 = 0xC0
	IIC_Wait_ACK();
	IIC_Send_Byte(Dn_H);
	IIC_Wait_ACK();
	IIC_Send_Byte(Dn_L);
	IIC_Wait_ACK();
	IIC_STOP();
}
