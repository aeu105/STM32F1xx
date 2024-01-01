#include "bsp_oled.h"


/*

寻址方式: 页寻址模式

整个屏幕像素128列*64行
其中 64 行分为 8 页(page0 ~ page7), 每页 8行 128列
写数据顺序:
	@1
		确定页
	@2
		确定列(列高地址/列低地址)
		由上到下: D0 ~ D7(先写低位, 分别写低四位,高四位)
*/ 
void OLED_Init(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);	// 此处置高电平, 片选信号低电平有效
	
	// Power ON
	// 来源: SSD1306驱动芯片手册 8.9 Power ON and OFF sequence
	OLED_RST_Set();
	Delay_us(100000);
	OLED_RST_Clr();
	Delay_us(20);	// 至少 3us 延时
	OLED_RST_Set();
	
	// Software Configuration
	// 来源: SSD1306驱动芯片手册
	// SSD1306 初始化
	OLED_WR_Byte(0xA8, OLED_CMD);	// 设置多路复用率
	OLED_WR_Byte(0x3F, OLED_CMD);
	
	OLED_WR_Byte(0xD3, OLED_CMD);	// 设置显示偏移
	OLED_WR_Byte(0x00, OLED_CMD);
	
	OLED_WR_Byte(0x40, OLED_CMD);	// 设置显示开始行
	OLED_WR_Byte(0xA1, OLED_CMD);	// 0xA0/0xA1: 控制屏幕左右映射
	OLED_WR_Byte(0xC8, OLED_CMD);	// 0xC0/0xC8: 控制屏幕上下映射
	
	// 10.1.18 Set COM Pins Hardware Configuration(DAh)
	OLED_WR_Byte(0xDA, OLED_CMD);	// 设置 COM 引脚硬件配置
	OLED_WR_Byte(0x12, OLED_CMD);	// DA02H: 隔行显示	DA12H: 逐行显示
	
	OLED_WR_Byte(0x81, OLED_CMD);	// 对比度设置(0x00~0xFF)
	OLED_WR_Byte(0x7F, OLED_CMD);
	
	OLED_WR_Byte(0xA4, OLED_CMD);	// 设置整个显示打开/关闭
	OLED_WR_Byte(0xA6, OLED_CMD);	// 0xA6: 阳码显示(没有显示的部分不发光)	0xA7: 阴码显示
	OLED_WR_Byte(0xD5, OLED_CMD);
	OLED_WR_Byte(0x80, OLED_CMD);
	
	OLED_WR_Byte(0x8D, OLED_CMD);
	OLED_WR_Byte(0x14, OLED_CMD);
	
	// 开启显示功能
	OLED_WR_Byte(0xAF, OLED_CMD);	// 0xAE: 关闭显示	0xAF: 开启显示
	
	
	OLED_Clear();	// 所有位写 0
	OLED_Set_Pos(0, 0);	// 初始位置设置
}

// dat: 写入的数据/命令内容
// cmd: 0 命令	1 数据
void OLED_WR_Byte(unsigned char dat, unsigned int cmd) {
	
	unsigned int i;
	
	
	if(cmd)	// D/C#: DC置高发数据, DC置低发命令
		// 1 数据
		OLED_DC_Set();
	else
		// 0 命令
		OLED_DC_Clr();
	
	
	OLED_CS_Clr();	// 片选信号线
	
	for(i = 0; i < 8; i++) {
		
		OLED_SCLK_Clr();	// 上升沿写入数据, 先置低位
		
		// 写入的数据内容
		if(dat & 0x80)
			OLED_SDIN_Set();
		else
			OLED_SDIN_Clr();
		
		OLED_SCLK_Set();	// 上升沿写入数据, 置高位
		dat <<= 1;
	}
	
	OLED_CS_Set();
}

void OLED_Clear(void) {	// 默认按页地址访问RAM, 9 COMMAND TABLE -> 3. Addressing Setting Command Table
	
	unsigned int i, j;
	for(i = 0; i < 8; i++) {	// 一共有 8 页
		
		OLED_WR_Byte((0xb0 + i), OLED_CMD);	// 设置 page 页地址, 取值: 0xb0~0xb7 (3. Addressing Setting Command Table)
		// 列地址, 高位/低位分开存放
		OLED_WR_Byte(0x00, OLED_CMD);	// 设置列地址的低位
		OLED_WR_Byte(0x10, OLED_CMD);	// 设置列地址的高位
		for(j = 0; j < 128; j++)
			OLED_WR_Byte(0x0, OLED_DATA);
	}
}
// 定义起始坐标
// x: 列(列低地址/列高地址)	y: 页(0xb0~0xb7)
void OLED_Set_Pos(unsigned int x, unsigned int y) {
	
	// 设置页地址
	OLED_WR_Byte((0xb0 + y), OLED_CMD);
	
	// 设置列地址
	// 例如: 向第3列写数据, 则传值 0000 0011
	// 低位 0011 放到低位地址, 转成 SSD1306 命令: 前四位补 0000
	// 高位 0000 放到高位地址, 转成 SSD1306 命令: 右移 4 位, 前面补 0001
	OLED_WR_Byte((x & 0x0F), OLED_CMD);	// 取出低四位(0x00~0x0F)
	OLED_WR_Byte((((x & 0xF0) >> 4) | 0x10), OLED_CMD);	// 取出高四位(0x10~0x1F)
}

/*
x0, y0: 起始位置
x1, y1: 结束位置

		x0		x1	(0~127)
(0	y0	.	.	.
		.	.	.
		.	.	.
7)	y1	.	.	.
*/
// 起始列, 起始页, 结束列, 结束页, 数组
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char bmp[]) {
	
	unsigned int i = 0;
	unsigned int x, y;
	for(y = y0; y <= y1; y++) {
		
		OLED_Set_Pos(x0, y);	// 列, 页
		for(x = x0; x <= x1; x++) {
			
			OLED_WR_Byte(bmp[i++], OLED_DATA);
		}
	}
}

void OLED_Set(void) {	// 默认按页地址访问RAM, 9 COMMAND TABLE -> 3. Addressing Setting Command Table
	
	unsigned int i, j;
	for(i = 0; i < 8; i++) {	// 一共有 8 页
		
		OLED_WR_Byte((0xb0 + i), OLED_CMD);	// 设置 page 页地址, 取值: 0xb0~0xb7 (3. Addressing Setting Command Table)
		// 列地址, 高位/低位分开存放
		OLED_WR_Byte(0x00, OLED_CMD);	// 设置列地址的低位
		OLED_WR_Byte(0x10, OLED_CMD);	// 设置列地址的高位
		for(j = 0; j < 128; j++)
			OLED_WR_Byte(0xFF, OLED_DATA);
	}
}
