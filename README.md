# STM32F1xx 基础教程 - 说明+源码



有关引脚利用库函数初始化步骤:

```c
//初始化结构体
xxxx_InitTypeDef xxxx_InitStructure;
//相关引脚的时钟使能
RCC_xxxxPeriphClockCmd(RCC_xxxxPeriph_xxxx, ENABLE);
//结构体成员变量赋值
xxxx_InitStructure.xxxx = xxxx;
//完成结构体初始化
xxxx_Init(&xxxx_InitStructure);
```

## 01 STM32 开发环境搭建

### 一. 基于Keil μVision 5开发环境搭建

软硬件：Windows 11 + C51V961.exe + MDK538A.exe

#### 1. Keil μVision 5 创建项目流程：

① 创建文件目录 `STM32F103C8T6`

| documents | files                                                        |
| --------- | ------------------------------------------------------------ |
| Doc       | README.md                                                    |
| Libraries | CMSIS<br />STM32F10x_StdPeriph_Driver                        |
| MDK-ARM   | STM32F103C8T6.uvprojx                                        |
| Output    | Listings<br />Objects                                        |
| User      | stm32f10x_conf.h<br />stm32f10x_it.c<br />stm32f10x_it.h<br />main.c<br />main.h |
|           | keilkill.bat                                                 |

② 打开 Keil μVision 5, 菜单栏 `Project >> New μVision Project...`

选择项目保存路径(Path: .\STM32F103C8T6\MDK-ARM\STM32F103C8T6.uvprojx)

※PS: 注意创建相应文件夹, 将项目相关文件保存在同一个文件目录中

③ 项目文件创建后弹出`Select Device for Target 'Target 1' ...`窗口, 选择设备Device: `STM32F103C8` >> OK

④ 点击`Manage Project Items`选项,  可按照以下选项创建项目虚拟文件目录:

| Project Targets |      Groups      |               files                |
| :-------------: | :--------------: | :--------------------------------: |
|  STM32F103C8T6  |     Startup      |       startup_stm32f10x_md.s       |
|                 |      CMSIS       | core_cm3.c<br />system_stm32f10x.c |
|                 | StdPeriph_Driver |     misc.c<br />stm32f10x_*.c      |
|                 |       User       |     stm32f10x_it.c<br />main.c     |
|                 |       Doc        |             README.md              |

以上相关文件路径:

**Startup** >>

​	.\STM32F103C8T6\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm\startup_stm32f10x_md.s

**CMSIS** >>

​	.\STM32F103C8T6\Libraries\CMSIS\CM3\CoreSupport\core_cm3.c

​	.\STM32F103C8T6\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\system_stm32f10x.c

**StdPeriph_Driver** >>

​	.\STM32F103C8T6\Libraries\STM32F10x_StdPeriph_Driver\src\\**.c

**User** >>

​	main.c

​	stm32f10x_it.c

**Doc** >>

​	.\STM32F103C8T6\Doc\README.md

⑤ 选项配置

打开 Options for Target '$STM32F103C8T6' 窗口:

1）Target选项:

~~Xtal(MHz): 72.0(STM32F103)~~<u>[晶振频率]</u>

ARM Compiler: **Use default compiler version 5**<u>[编译器版本]</u>

2）Output选项:

勾选 **Create HEX File**

3）C/C++选项:

| Define[宏定义]                     | Include Paths                                                |
| ---------------------------------- | ------------------------------------------------------------ |
| STM32F10X_MD, USE_STDPERIPH_DRIVER | .\STM32F103C8T6\Libraries\CMSIS\CM3\CoreSupport<br />.\STM32F103C8T6\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x<br />.\STM32F103C8T6\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm<br />.\STM32F103C8T6\Libraries\STM32F10x_StdPeriph_Driver\inc<br />.\User |

#### 2. 编译环境测试:

`main.h`

```c
#ifndef __MAIN_H__
#define __MAIN_H__


#include <stm32f10x.h>


#edndif	/* __MAIN_H__ */

```

`main.c`

```c
#include "main.h"


int main(void) {
    
	while(1) {
        
        // 循环体
	}
    
    // return 0;
}

```


※PS:

编译报错:

​	Target > Code Generation：**Use default compiler version 5**

字符编码:

​	Edit > Configuration > Encoding：**UTF-8**

文件编辑:

​	Libraries文件夹 - `只读`选项

F4xx固件库编译报错:

​	stm32f4xx.h文件编译错误:  stm32f4xx_fsmc.c、stm32f4xx_fmc.c

```c
11580	//Legacy aliases遗留的别名--此块代码进行注释
/* Legacy aliases */
#define  DBGMCU_APB2_FZ_DBG_TIM1_STOP        DBGMCU_APB1_FZ_DBG_TIM1_STOP    
#define  DBGMCU_APB2_FZ_DBG_TIM8_STOP        DBGMCU_APB1_FZ_DBG_TIM8_STOP
#define  DBGMCU_APB2_FZ_DBG_TIM9_STOP        DBGMCU_APB1_FZ_DBG_TIM9_STOP
#define  DBGMCU_APB2_FZ_DBG_TIM10_STOP       DBGMCU_APB1_FZ_DBG_TIM10_STOP
#define  DBGMCU_APB2_FZ_DBG_TIM11_STOP       DBGMCU_APB1_FZ_DBG_TIM11_STOP
11585
```

### 二 基于开发环境搭建



※数据参考来源:

(1)  标准外设库下载([STM32标准外设软件库](https://www.st.com/zh/embedded-software/stm32-standard-peripheral-libraries.html))

STM32F10x标准外设库(en.stsw-stm32054_v3-6-0_v3.6.0.zip): https://www.st.com/zh/embedded-software/stsw-stm32054.html



<hr>

## 02 利用寄存器点亮 LED 灯

### 功能描述：

​	通过配置寄存器控制板载 LED (PC13)闪烁

### 代码实现:

```c
#include "main.h"

// 注意'()'的使用
// volatile 从寄存器取值
#define RCC_APB2ENR_GPIOC (((volatile unsigned long)(0x40021000 + 0x18)))

void Delay(unsigned long nCount);

int main(void) {
    
    // RCC_APB2ENR 时钟使能 GPIOC
    //*((unsigned long*)(0x40021000 + 0x18)) |= 0x00000010;	// RCC_APB2ENR 开启 GPIOC 时钟
    RCC_APB2ENR_GPIOC |= 0x00000010;
    
    // GPIOC_13 端口配置高寄存器 通用推挽输出 50MHz
    // 0x40011000 数值, 需强制转化为地址
    // (unsigned long*)0x40011000 地址, 需取出值进行重新赋值
    *((unsigned long*)(0x40011000 + 0x04)) &= 0xFF0FFFFF;	// GPIOC_CRH 13 位清零
    *((unsigned long*)(0x40011000 + 0x04)) |= 0x00300000;	// GPIOC_CRH 13 位通用推挽输出 50MHz
    
    *((unsigned long*)(0x40011000 + 0x0c)) &= 0xFFFF0FFF;	// GPIOC_ODR 13置0
    
    while(1) {
        
        *((unsigned long*)(0x40011000 + 0x0c)) |= 0x00002000;	// GPIOC_ODR 13位 置1 LED13 亮
        Delay(0xFFFFF);
        *((unsigned long*)(0x40011000 + 0x0c)) &= 0xFFFF0FFF;	// GPIOC_ODR 13位 置0 LED13 灭
        Delay(0xFFFFF);
    }
}

void Delay(unsigned long nCount) {
    
    while(nCount--);
}

```

### 代码分析:

※寄存器地址 = ①基地址 + ②偏移地址

1）GPIOC 时钟使能(RCC 寄存器):

```c
*((unsigned long*)(0x40021000 + 0x18)) |= 0x00000010;	// RCC_APB2ENR 开启 GPIOC 时钟
```

​	根据 STM32F103Cx_en.pdf -> Figure 1. STM32F103xx performance line block diagram 确认`GPIOC 时钟`挂载在` APB2 总线`上, 然后根据 STM32中文参考手册_V10.pdf -> 7.3.7 APB2 外设时钟使能寄存器(RCC_APB2ENR) 对 GPIOC 时钟进行使能(RCC_APB2ENR 寄存器第4位置1开启GPIOC时钟)

​	① APB2 基地址: 0x40021000 (STM32F103Cx_en.pdf -> 4 Memory mapping -> Figure 11. Memory map）	

​	② APB2 外设时钟使能寄存器(RCC_APB2ENR)偏移地址: 0x18 (STM32中文参考手册_V10.pdf -> 7.3.7 APB2 外设时钟使能寄存器(RCC_APB2ENR))

​	③ APB2 外设时钟使能寄存器地址: 0x40021000 + 0x18 = 0x40021018

​	④ RCC_APB2ENR 第4位置1 (| 操作)

2）GPIOC 引脚模式配置:

```c
*((unsigned long*)(0x40011000 + 0x04)) &= 0xFF0FFFFF;	// GPIOC_CRH 13 位清零
*((unsigned long*)(0x40011000 + 0x04)) |= 0x00300000;	// GPIOC_CRH 13 位通用推挽输出 50MHz
```

​	根据 STM32F103C8T6原理图.pdf 确认 LED 接在 GPIOC_13 引脚, 根据 STM32中文参考手册_V10.pdf -> 8.2.2 端口配置高寄存器(GPIOx_CRH) (x=A..E) 配置引脚模式为`通用推挽输出模式`.

​	0\~7 低位 8\~15 高位	GPIOC_13 位于高位寄存器

​	端口配置高寄存器(GPIOx_CRH) CNF13 / MODE13 配置为 `0011` -- 通用推挽输出模式, 最大速度50MHz

​	① GPIOC 基地址: 0x40011000 （STM32F103Cx_en.pdf -> 4 Memory mapping -> Figure 11. Memory map）	

​	② GPIOC 端口配置高寄存器偏移地址: 0x04 (STM32中文参考手册_V10.pdf -> 8.2.2 端口配置高寄存器(GPIOx_CRH) (x=A..E))

​	③ GPIOC 端口配置高寄存器地址: 0x40011000 + 0x04 = 0x40011004

​	④ GPIOx_CRH 第13组[CNF / MODE]配置为 0011

3）GPIOC 引脚写数据(输出高低电平):

```c
*((unsigned long*)(0x40011000 + 0x0C)) &= 0xFFFF0FFF;	// GPIOC_ODR 13位 置0
*((unsigned long*)(0x40011000 + 0x0C)) |= 0x00002000;	// GPIOC_ODR 13位 置1
```

​	根据 STM32F103C8T6原理图.pdf 确认当 GPIOC_13 输出低电平时, LED 点亮, 输出高电平时, LED 熄灭.

​	① GPIOC端口输出数据寄存器偏移地址：0x0C

​	② GPIOC端口输出数据寄存器地址：0x40011000 + 0x0C = 0x4001100C

​	③ GPIOx_IDR 第13位置位(| 置1 / & 置0)

※总结:

1） 相应引脚时钟使能(GPIOC时钟使能)

```c
*((unsigned long*)(0x40021000 + 0x18)) |= 0x00000010;
```

2） 寄存器初始化

```c
*((unsigned long*)(0x40011000 + 0x04)) &= 0xFF0FFFFF;
*((unsigned long*)(0x40011000 + 0x04)) |= 0x00300000;
```

3） 寄存器赋值

```c
*((unsigned long*)(0x40011000 + 0x0C)) |= 0x00002000;	// GPIOC_ODR_13 置1
*((unsigned long*)(0x40011000 + 0x0C)) &= 0xFFFF0FFF;	// GPIOC_ODR_13 置0
```

### 参考资料:

STM32F103Cx_en.pdf

STM32中文参考手册_V10.pdf

STM32F103C8T6原理图.pdf



<hr>

## 03 利用库函数点亮 LED 灯



### 功能描述:

​	利用库函数控制板载 LED 闪烁

### 代码实现:

```c
#include <stm32f10x.h>


void Delay_us(unsigned long nCount);
void GPIOC_Configuration(void);

int main(void) {
    
    GPIOC_Configuration();	// GPIOC 初始化
    
    while(1) {
        
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        Delay_us(1000000);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        Delay_us(1000000);
    }
}

void GPIOC_Configuration(void) {
    
    GPIO_InitTypeDef GPIO_InitStructure;	// 定义结构体
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	// 使能 GPIOC 时钟
    // 结构体变量赋值
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	// PC13 引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 输出速度 50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);	// 完成 GPIOC 端口初始化配置
}

void Delay_us(unsigned long nCount) {
    
    while(cCount--);
}

```

### 代码分析:

1） GPIOC 时钟使能

```c
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
```

2） GPIOC_13 引脚配置

```C
GPIO_InitTypeDef GPIO_InitStructure;

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOC, &GPIO_InitStructure);
```

3） 引脚赋值

```c
GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);	// 置0
GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);	// 置1
```

### 参考资料:




<hr>

## 04 利用按键控制 LED 状态

### 功能描述:

​	利用按键改变板载 LED 状态(亮变灭, 灭变亮)

|   引脚   |      |
| :------: | :--: |
| GPIOA_0  | KEY  |
| GPIOC_13 | LED  |



### 代码实现:

```c
#include <stm32f10x.h>

#define KEY_ON	0	// 按键按下 低电平
#define KEY_OFF	1	// 按键未按下 高电平


void GPIOC_Configuration(void);	// LED 引脚配置
void GPIOA_Configuration(void);	// 按键 引脚配置
int Key_Scan(void);
void Delay_us(unsigned long nCount);


int main(void) {
    
    GPIOC_Configuration();	// GPIOC 初始化 -- LED
    
    GPIOA_Configuration();	// GPIOA 初始化 -- KEY 按键
    
    // GPIO_RestBits(GPIOC, GPIO_Pin_13);	// 初始状态 LED 点亮
    
    while(1) {
        
        if(KEY_ON == Key_Scan()) {	// 检测按键是否按下
            
            while(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));	// 循环检测, 当按键抬起时改变状态
            GPIOC->ODR ^= GPIO_Pin_13;	// 异或操作, 相同为0不同为1, LED状态取反
        }
    }
}

void Delay_us(unsigned long nCount) {
    
    while(nCount--);
}

int Key_Scan(void) {	// 检测按键状态
    
    // 读取 GPIOA_0 引脚状态
    if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
        
        Delay_us(0xFF);	// 延时, 消除抖动
        if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
            
            return KEY_ON;	// 经过以上两个 if 进行判断后, 按键确实按下, 返回状态(按键已按下)
        }
        
        return KEY_OFF;	// 经过第一次 if 判断后, 未进入第二次 if 判断, 可以认为是一次偶然的低电平(返回状态按键未按下)
    }
    
   return KEY_OFF;	// 未进入 if 判断, 按键未按下, 返回状态(按键未按下)
}
// 按键 引脚模式初始化
void GPIOA_Configuration(void) {
    
    // 定义结构体
    GPIO_InitTypeDef GPIO_InitStructure;	
	// RCC 时钟使能 GPIOA, 挂载在 APB2 总线上
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// 成员变量赋值
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 内部上拉输入模式, 当按键未按下时, 此引脚状态为高电平
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
// LED 引脚模式初始化
void GPIOC_Configuration(void) {
    
    // 定义结构体
    GPIO_InitTypeDef GPIO_InitStructure;
	// RCC 时钟使能 GPIOC, 挂载在 APB2 总线上
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	// 成员变量赋值
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

```

### 代码分析:

※流程:

​	1） GPIOC 配置(通用推挽输出模式)

```c
void GPIOC_Configuration(void) {
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
```

​	2） GPIOA 配置(内部上拉输入模式)

```c
void GPIOA_Configuration(void) {
    
	GPIO_InitTypeDef GPIO_InitStructure;
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
```

​	3） 检测 GPIOA_0 引脚状态, 当为 0 时(即按键被按下), GPIOC_13 引脚状态反转

```c
if(0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
    
    GPIOC->ODR ^= GPIO_Pin_13;
}
```

### 参考资料:



<hr>

## 05 呼吸灯

### 功能描述:

​	实现 LED 呼吸灯效果(涉及知识点: 占空比)

### 代码实现:

```c
#include <stm32f10x.h>

#define TIME 3000	// 周期


void GPIOC_Configuration(void);
void Delay_us(unsigned long nCount);

int main(void) {
    
    unsigned long i;
    
    GPIOC_Configuration(void);
    
    while(1) {
        
        for(i = 0; i <= TIME; i++) {	// GPIO 由灭变亮, 低电平越来越长
			
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
			Delay_us(i);
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
			Delay_us(TIME - i);
		}
		
		for(i = 0; i <= TIME; i++) {	// GPIO 由亮变灭, 高电平越来越长
			
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
			Delay_us(i);
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
			Delay_us(TIME - i);
		}
    }
}

void Delay_us(unsigned long nCount) {
    
    while(nCount--);
}

void GPIOC_Configuration(void) {
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

```

### 代码分析:

```c
for(i = 0; i <= TIME; i++) {	// GPIO 由灭变亮, 低电平越来越长
    
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
	Delay_us(i);	// 周期内低电平时间增加
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
	Delay_us(TIME - i);	// 周期内高电平时间减少
}

for(i = 0; i <= TIME; i++) {	// GPIO 由亮变灭, 高电平越来越长

    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
    Delay_us(i);	// 周期内高电平时间增加
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
    Delay_us(TIME - i);	// 周期内低电平时间减少
}

```



### 参考资料:

​	占空比	

​	单位时间内流经 LED 高电平的时间



<hr>

## 06 利用中断控制 LED 状态

### 功能描述:

​	利用`外部中断`功能改变 LED 状态(亮变灭, 灭变亮)

​	当检测到 GPIOA_0 引脚电平发生改变时, 产生 EXTI0 中断 

### 代码实现:

```c
#include <stm32f10x.h>

void GPIOC_Configuration(void);
void PA0_EXTI0_Configurstion(void);

int main(void) {
    
    GPIOC_Configuration();
    
    PA0_EXTI0_Configuration();	// 外部中断初始化配置
    
    while(1) {
        
        //
    }
}
// EXTI0 的中断处理函数, 当发生 EXTI0 中断时, 必定跳转至此函数
void EXTI0_IRQHandler(void) {
    
    if(SET == EXTI_GetITStatus(EXTI_Line0)) {	// 判断是否真正触发了中断请求
        
		GPIOC->ODR ^= GPIO_Pin_13;	// 异或操作(不同为 1, 相同为 0), 翻转当前 LED 状态
		EXTI_ClearITPendingBit(EXTI_Line0);	// 清除中断标志位!!! 重要, 否则会持续进中断
	}
}

void PA0_EXTI0_Configuration(void) {
    
    NVIC_InitTypeDef NVIC_InitStructure;	// ->-向量中断控制器-<-
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;	// ->-外部中断/事件控制器-<-
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	// 需要开启功能复用 IO 时钟(外部中断功能)
    
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;	// 使能指定的 IRQ 通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	// 抢占优先级, 响应优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	// 从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	// 使能 IRQ 通道
	NVIC_Init(&NVIC_InitStructure);	// 完成初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 内部上拉输入, 默认高电平状态
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	// 开启引脚的外部中断模式
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;	// 使能外部中断线 0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	// 中断模式为中断请求
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	// 下降沿触发, 当 GPIOA_0 引脚检测到高电平变为低电平时, 触发中断
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	// 使能中断
	EXTI_Init(&EXTI_InitStructure);	// 完成 EXTI 寄存器初始化
}

void GPIOC_Configuration(void) {
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

```

### 代码分析:



### 参考资料:





<hr>

## 07 SysTick 滴答定时器

### 功能描述:

​	配置 SysTick, 实现LED闪烁的精确延时

### 代码实现:

```c
#include <stm32f10x.h>


void GPIOC_Configuration(void)；
void SysTick_Configuration(void)；
void Delay_us(unsigned long nCount)；


//extern unsigned long TimingDelay;	// SysTick_Handler()函数中需要使用此参数
unsigned long TimingDelay;

int main(void) {
    
    SysTick_Configuration();	// 滴答定时器SysTick初始化配置
    
    GPIOC_Configuration();
    
    while(1) {
        
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		Delay_us(50000);	// 1s = 1000ms = 1000000us
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		Delay_us(50000);
    }
}

void Delay_us(unsigned long nCount) {
    
    TimingDelay = nCount;
	
	SysTick->CTRL |= (1<<0);	// STK_CTRL 0位置1, 开启计数
	
	while(TimingDelay);	// 等待数值减完, 用时 TiningDelay 微秒
	
	SysTick->CTRL &= ~(1<<0);	// STK_CTRL 0位置0, 关闭计数
}
// 中断函数位于'stm32f10x_it.c'文件中
void SysTick_Configuration(void) {	// STK 初始化函数
    
    // 初始化使能定时器, 1us 进一次中断
    while(SysTick_Config(72));		// 库函数完成 STK 使能(STK_CTRL低3位取值 111), 并装载值 72(取值依据: AHB时钟频率)
    
	SysTick->CTRL &= ~(1<<0);	// 未使用时关闭定时器--寄存器控制CTRL第 0 位清零, 关闭计数, 待使用前开启
								// 1<<0 -> 1
								// ~(1<<0) -> 0
}

void GPIOC_Configuration(void) {
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

```

```c
// 中断函数
void SysTick_Handler(void) {	// STK 中断函数, 当 STK 装载值减至 0 时会跳转至此函数, 根据频率 72MHz 以及 装载值 72, 计算进一次此中断用时 1us
	
	if(0 != TimingDelay) {		// 判断延时值是否减完, 即是否延时时间到
        
        TimingDelay--;
    }
}

```

### 代码分析:

SysTick timer(STK) 24-bit(计数范围: 0~((2^24)-1))

相关寄存器:

1）STK_CTRL(控制寄存器)

​	关于计数周期的计算:

​		总时间T = 减数的个数nCount * 减一个数所用时间t

2）STK_LOAD(重装载寄存器)

​	重装载值取值说明:

​		工作频率取值 AHB 时钟频率: 72MHz, 则周期 T=1/f = 1/72000000(此为减一个数所用时间), 当装载值取值 72 时, 则装载值从 72 减至 0 用时 （1/72000000)*72=1us, 此时会进入一次 SysTick_Handler() 中断(装载值减至 0 就会进入一次此中断), 综上, 进几次 SysTick_Handler() 中断就会用时几微秒, 程序中取值 1000000, 即为延时 1s.

3）STK_VAL(当前计数值)

4）STK_CALIB(校准)

### 参考资料:

​	STM32F10xxx Cortex-M3编程手册.pdf -> 4.5 SysTick timer(STK)



<hr>

## 08 IWDG 独立看门狗

### 功能描述:

​	验证 IWDG 工作流程

​	IWDG: 计数值达到给定的超时值时, 会产生系统复位

### 代码实现:

```c
#include <stm32f10x.h>


void GPIOC_Configuration(void);
void SysTick_Configuration(void);
void Delay_us(unsigned long nCount);
void IWDG_Configuration(void);


int main(void) {
    
    SysTick_Configuration();
    GPIOC_Configuration();
    
    // 开始 IWDG 初始化配置
    IWDG_Configuration();
    // 完成 IWDG 初始化配置
    // 并开始计数
    
    // 此段仅在上电(复位)时执行
	// @1 LED闪烁
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);	// LED 亮
	Delay_us(500000);	// 延时 500ms
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);	// LED 灭
	Delay_us(400000);	// 延时 400ms
    // 结束计数, 此时间约 500 + 400 = 900 ms < 1000 ms (1000 依据: 以上说明中 ->-产生IWDG复位所需总时间T-<-) 
	// 以上 MCU 启动后从开始到完成 IWDG 初始化配置约 900ms 进入 while() 循环体, 此时间 < 1000 ms, 不会产生 IWDG 复位
    // 验证: 更改以上总延时时间 > 1000 ms, 程序不会进入到 while() 循环体, 现象: LED 闪烁[频繁复位]
    
    while(1) {	// 当以上总延时时间 < 1000 ms 时, 进入此循环体
        
        IWDG_ReloadCounter();	// IWDG 重装载(重置计数值)
        // @2
        // 最大值<1000000, 因为>=1000000会复位
		Delay_us(900000);	// 延时 900ms(< 1000 ms) 后重装载计数值, 不会产生 IWDG 复位
        // 验证: 更改此处延时时间 > 1000 ms, 产生 IWDG 复位, 现象: LED 闪烁(此现象会在 LED 一次亮灭后有-停滞感[延时时间: while()前延时+while()内延时]-)
    }
}

void IWDG_Configuration() {	// IWDG 初始化
    
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	// 使能对寄存器 IWDG_PR 和 IWDG_RLR 的写操作
	IWDG_SetPrescaler(IWDG_Prescaler_64);	// 设置 IWDG 的预分频值
	IWDG_SetReload(625);	// 设置 IWDG 的重装载值 (T = t * nCount = (64 / 40kHz) * 625 = 1s 不进行重装载则产生复位)
	IWDG_ReloadCounter();	// 按照 IWDG 重装载寄存器的值重装载 IWDG 计数器
	IWDG_Enable();	// 使能 IWDG,  即刻开始计数
}

```

### 代码分析:

​	时钟源: LSI (频率按照 40kHz[非准确值: 30~60之间] 计算)

※相关寄存器:

1）IWDG_KR(键寄存器)

​	作用: ->-使 IWDG 可以使用-<-

​	程序运行时以一定时间间隔写入 0xAAAA, 否则计数值为 0 时, 会产生看门狗复位

2）IWDG_PR(预分频寄存器)

​	工作频率, 对 LSI 进行分频设置 IWDG_PR = 4 * 2^PR(PR取值 000~111), 按照 LSI 频率 40kHz, 此处 IWDG_PR 取值 64

​	最终工作频率 f = 40kHz / IWDG_PR = 40kHz / 64

​	寄存器减一个数需要用时:

​		t = 1 / f = IWDG_PR / 40kHz (此处预分频因子取值 100, 即IWDG_PR = 64) = 1.6 ms

3）IWDG_RLR(重装载寄存器)

​	设置计数器的初始值, 此处取值 625.

​	产生 IWDG 复位所需总时间T:

​		T(寄存器减一个数用时t * 减数的个数nCount) = t * nCount = 1.6 * 625 = 1000 ms

4）IWDG_SR(状态寄存器)

### 参考资料:



<hr>

## 09 WWDG 窗口看门狗

### 功能描述:

​	验证 WWDG 工作流程

### 代码实现:

```c
#include <stm32f10x.h>


void SysTick_Configuration(void);
void GPIOC_Configuration(void);
void WWDG_Configuration(unsigned char tr, unsigned char wr, unsigned int pre);
void WWDG_NVIC_Configuration(void);


int main(void) {
    
    SysTick_Configuration();
    GPIOC_Configuration();
    
    // 上电(复位)时执行
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);	// LED 亮
	Delay_us(1000000);
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);	// LED 灭
	Delay_us(1000000);
    
    // 装载计数值, 上窗口值, 预分频值
	WWDG_Configuration(0x7F, 0x5F, WWDG_Prescaler_4);	// WDGTB取值2
    
    // @1非刷新区域: LED 间隔 1s 持续闪烁[复位]
    // 此处[立即]或[延时<14563.556us]进行喂狗操作, 将产生复位
    // 时间计算: 从 0x7F(127)减到0x5F(95)共计减32个数
    // 用时约t = nCount * (1 / f) = 32 * ((4096 * (2^2)) / 36MHz) = 14563.55556us.
	Delay_us(14000);	// 延时数值 < 14563.556us
	WWDG_SetCounter(WWDG_CNT);
	
	// @2刷新区域: LED 间隔 1s 闪烁 2 次后 0.5s 持续闪烁
	// 此处 [延时>14563.556us] 且 [延时<28672us] 进行喂狗操作, 延时>28672us时已进中断
	Delay_us(15000);	// 延时数值 > 14563.56us
	WWDG_SetCounter(WWDG_CNT);
    
    while(1) {
        
        // 进 WWDG 中断后若不执行喂狗操作则产生复位操作, 此处代码不执行
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		Delay_us(50000);
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		Delay_us(50000);
    }
}

void WWDG_NVIC_Configuration(void) {
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;	// 使能 WWDG 的中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

unsigned char WWDG_CNT = 0x7F;
void WWDG_Configuration(unsigned char tr, unsigned char wr, unsigned int pre) {
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	// WWDG 时钟使能
	
	WWDG_CNT &= tr;	// 防止参数 > 0x7F
	WWDG_SetPrescaler(pre);	// 设置 WWDG 预分频值
	//WWDG_SetCounter(0x7F);	// 设置计数值, 从哪个数开始减
	WWDG_SetWindowValue(wr);	// 设置 WWDG 窗口值
	
	WWDG_NVIC_Configuration();	//涉及到 WWDG_IRQHandler() 中断, 需要对 NVIC 进行配置
	
    // 注意开启位置, 需要在中断使能之前
	WWDG_Enable(WWDG_CNT);	// 使能 WWDG 并装载计数值,	此处 WWDG_Enable() 具有装载初始值的功能, 可以省略上面的 WWDG_SetCounter() 函数
	
    WWDG_ClearFlag();	// !清除早期唤醒中断标志位
	WWDG_EnableIT();	// 使能 WWDG 早期唤醒中断（ EWI）
	
	// WWDG_Enable(WWDG_CNT);	// 使能 WWDG 并装入计数器值
}

void WWDG_IRQHandler(void) {	// 当 WWDG 计数值减至 0x40 时会跳转至此函数, 处理时间<455.111us
	
	WWDG_SetCounter(WWDG_CNT);	// 重置重装载值(喂狗)
	
	WWDG_ClearFlag();	// 清除中断标志位
}

```

### 代码分析:

WWDG:

​	配置有: ①递减(装载)计数器值 ②上窗口值,

​		1）当计数器值从设置值向下递减至上窗口值之前时, 不能进行重置计数器值(喂狗)操作;

​		2）当计数器值减至上窗口值与 0x40 之间时, 可以~~(必须)~~进行重置计数器值(喂狗)操作;

​		3）当计数器值减至 0x40 时, 若使能了 WWDG_CFR 寄存器的 EWI 位, 则会产生一个中断跳转至 WWDG_IRQHandler() 函数, 可以在此中断函数内进行重置计数器值(喂狗)操作(不建议).

※相关寄存器:

1）WWDG_CR: 控制寄存器, 使能 WWDG 以及存储计数器值

2）WWDG_CFR: 配置寄存器, 设置上窗口值, 预分频值以及 EWI 中断使能

​	工作频率: f = ((PCLK1 / 4096) / (2^WDGTB))

​	减一个数用时: t = 1 / f = (4096 * (2^WDGTB)) / PCLK1

​	超时值计算:

​			最小 <-> 最大计数个数: T[5:0] + 1 = 1 <-> 64

​			(最小: 0x40 -> 0x3F) (最大: 0x7F -> 0x3F)[当减至0x3F时产生复位]

​	在 PCLK1 = 36 MHz 时的最小-最大超时值(T = t * nCount):

| wdgtb |  min  |   max   |
| :---: | :---: | :-----: |
|   0   | 113us | 7.28ms  |
|   1   | 227us | 14.56ms |
|   2   | 455us | 29.12ms |
|   3   | 910us | 58.25ms |

2）WWDG_SR: 状态寄存器, EWIF 软件写 '0' 清除中断标志

### 参考资料:



<hr>

## 10 USART 配置及字符发送

### 功能描述:

​	通过 USART 发送字符

### 代码实现:

```c
#include <stm32f10x.h>

void SysTick_Configuration(void);
void USART1_Configuration(void);

int main(void) {
    
    SysTick_Configuration();
    
    USART1_Configuration();	// USART1 初始化配置
    
    while(1) {
        
        USART_SendData(USART1, 0x41);	// 发送 0x41 对应的字符 'A' (ASCII码表)
        Delay_us(1000000);
    }
}

void USART1_Configuration() {	// USART1 初始化
    
    GPIO_InitTypeDef GPIO_InitStructure;	// 需要使用 GPIO 引脚
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);	// 对应时钟使能
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	// TX -> RX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出, TX输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	// RX -> TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 浮空输入, RX接收
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = 115200;	// USART 传输的波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;	// 在一个帧中传输或者接收到的数据位数 8位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;	// 定义发送的停止位数目
    USART_InitStructure.USART_Parity = USART_Parity_No;	// 奇偶校验位失能
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 硬件流控制失能
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	// 发送 | 接收 使能
    USART_Init(USART1, &USART_InitStructure);	// 完成初始化配置
    
    USART_Cmd(USART1, ENABLE);	// 使能 USART1 外设
}

```

### 代码分析:



### 参考资料:



<hr>

## 11 USART 发送字符串

### 功能描述:

​	通过 USART 发送字符串

### 代码实现:

```c
#include <stm32f10x.h>
#include <stdio.h>

void SysTick_Configuration(void);
void USART1_Configuration(u32 BaudRate);
void USART1_SendString(const unsigned char *pt);

int main(void) {
    
    SysTick_Configuration();
    
    USART1_Configuration(115200);	// UASRT1 初始化配置
    
    while(1) {
        
        // 方式一
        USART1_SendString("Hello World!\n");	// 通过 USART1 发送字符串
        // 方式二
        printf("Hello World!\n");	// 通过改写 fputc() 发送字符串
    }
}

int fputc(int c, FILE *fp) {	// 改写 fputc(), 通过 USART1 '显示'
    
    while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TXE));
    USART_SendData(USART1, c);
    while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TC));
    
    return 0;
}

void USART1_SendString(const unsigned char *pt) {	// 字符串发送
    
    while(*pt) {	// 两处 while() 循环, 当发送数据寄存器为空或数据发送完成时返回 SET 值, 即当判断获取的值!=SET时, 跳出循环
        
        while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TXE));	// 发送数据寄存器空标志位, 当发送缓冲区为空时, 进行下面的数据发送
        USART_SendData(USART1, *pt);	// 发送字符
        while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TC));	// 发送完成标志位, 循环等待 USART_DR 寄存器内数据发送完毕
        pt++;	// 指向下一位数据
    }
}

// USART1: PA9 TX / PA10 RX
void USART1_Configuration(u32 BaudRate) {
    
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	// TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	// RX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = BaudRate;	// 波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;	// 停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 流控失能
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	// 使能模式
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);	// 使能 USART1 外设
}

```

### 代码分析:

### 参考资料:



<hr>

## 12 USART 接收数据



例程说明:

​	利用 UASRT 中断实现字符接收并输出

代码:

```c
#include <stm32f10x.h>

void USART1_Configuration(void);

int main(void) {
    
    SysTick_Configuration();
    USART1_Configuration();
    
    while(1) {
        //
    }
}

// USART1: PA9 TX / PA10 RX
void USART1_Configuration() {
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	// TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	// RX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	// 使能 USART 的接收中断
    USART_Cmd(USART1, ENABLE);	// 使能 USART1 外设
        
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	// 使能 USART1 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
// USART1 中断
void USART1_IRQHandler() {
    while(SET == USART_GetFlagStatus(USART1, USART_FLAG_RXNE)) {	// 接收数据寄存器非空返回 SET
        printf("%c", USART_ReceiveData(USART1));
    }
    printf("\n");
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}
int fputc(int c, FILE *fp) {	// 改写 fputc(), 通过 USART1 '显示'
    while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TXE));
    USART_SendData(USART1, c);
    while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TC));
    
    return 0;
}

```



### 13 STM32低功耗模式 - 睡眠模式

例程说明:

​	CPU上电启动后 ->

​		1. PC13位 LED 闪烁 5 次后程序调用 __WFI() 进入睡眠模式, 此时现象为: LED 间隔 1000000 us 闪烁 5 次后不再闪烁.

​		2. 当外部 PA0 按键按下后(EXTI0 中断), CPU 被唤醒, 继续执行 while() 语句其余部分, PC13位 LED 闪烁 5 次后进入下一周期的 while() 循环, 此时现象为: LED 间隔 200000 us 闪烁 5 次, 间隔 1000000 us 闪烁 5 次(下一轮循环)后不再闪烁(进入睡眠模式)

​		3. 重复 1. ~ 2.



代码:

```c
#include <stm32f10x.h>

void GPIOC_Configuration(void);
void PA0_EXTI0_Configuration(void);

int main(void) {
    
    unsigned int nCount;
    
    SysTick_Configuration();
    GPIOC_Configuration();
    
    while(1) {
        for(nCount = 0; nCount < 5; nCount++) {	// 延时间隔 1s
            GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
			Delay_us(1000000);
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
			Delay_us(1000000);
        }
        // __WFI() 进入睡眠模式, 通过任一中断唤醒(PA0 EXTI0中断)
        __WFI();
        for(nCount = 0; nCount < 5; nCount++) {	// 延时间隔 0.2s
            GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
			Delay_us(200000);
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
			Delay_us(200000);
        }
    }
}

void PA0_EXTI0_Configuration() {	// PA0_EXTI0 中断
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	// PA0 用作外部中断功能, 需开启复用功能时钟
    
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;	// 使能外部中断线 0 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;	// 使能外部中断线 0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	// 中断请求
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	// 下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	// 使能
	EXTI_Init(&EXTI_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_EXTILineConfig(GPIO_PortSource_GPIOA, GPIO_PinSource0);	// 使用外部中断线路
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void GPIOC_Configuration() {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void EXTI0_IRQHandler() {
    EXTI_ClearITPendingBit(EXTI_Line0);	// 清除 EXTI0 线路挂起位
}

```



### 14 STM32低功耗模式 - 停止模式

例程说明:

​	进入停止模式会关闭 HSI / HSE, 当唤醒后 HSE 不会被唤醒, 需要重新初始化, 此工作可在中断函数中进行.

​		参考代码来源: system_stm32f10x.c -> SetSysClockTo72()

​	进入停止模式:

​		①开启 PWR 时钟:
​			RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

​		②调用库函数进入停止模式:
​			PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);

​	停止模式唤醒方式: 任一中断

​	注:
​		调用中断后需 [清除] 中断标识位！！！

代码:

```c
#include <stdio.h>

void Delay_us(unsigned long nCount);
void GPIOC_Configuration(void);
void PA0_EXTI0_Configuration(void);
void STOP_Configuration(void);
void SetSysClockTo72MHz(void);

int main(void) {
    
    unsigned int nCount;
    
    SysTick_Configuration();
    GPIOC_Configuration();
	PA0_EXTI0_Configuration();
    
    while(1) {
        
        for(nCount = 0; nCount < 5; nCount++) {	// 延时间隔 0.2s
            GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
			Delay_us(200000);
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
			Delay_us(200000);
        }
        // 进入停止模式
        STOP_Configuration();
        
        for(nCount = 0; nCount < 5; nCount++) {	// 延时间隔 0.2s
            GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
			Delay_us(200000);
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
			Delay_us(200000);
        }
    }
}

void PA0_EXTI0_Configuration() {	// PA0_EXTI0 中断, 下降沿触发
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	// PA0 用作外部中断功能, 需开启复用功能时钟
    
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;	// 使能外部中断线 0 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;	// 使能外部中断线 0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	// 中断请求
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	// 下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	// 使能
	EXTI_Init(&EXTI_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_EXTILineConfig(GPIO_PortSource_GPIOA, GPIO_PinSource0);	// 使用外部中断线路
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void STOP_Configuration() {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
}
void GPIOC_Configuration() {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

// HSE TO 72MHz, 来源: system_stm32f10x.c
void SetSysClockTo72MHz() {
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
    
    /* Wait till HSE is ready and if Time out is reached exit */
    do {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    
    if ((RCC->CR & RCC_CR_HSERDY) != RESET) {
        HSEStatus = (uint32_t)0x01;
    }
    else {
        HSEStatus = (uint32_t)0x00;
    }
    
    if (HSEStatus == (uint32_t)0x01) {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        
        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

		/* HCLK = SYSCLK */
		RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
		/* PCLK2 = HCLK */
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;

		/* PCLK1 = HCLK */
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

#ifdef STM32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/
        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8 MHz */

        RCC->CFGR2 &= (uint32_t)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
                                    RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
        RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 |
                                    RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);

        /* Enable PLL2 */
        RCC->CR |= RCC_CR_PLL2ON;
        /* Wait till PLL2 is ready */
        while((RCC->CR & RCC_CR_PLL2RDY) == 0) {
        }


        /* PLL configuration: PLLCLK = PREDIV1 * 9 = 72 MHz */
        RCC->CFGR &= (uint32_t)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 | 
                                RCC_CFGR_PLLMULL9); 
    #else
        /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                            RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
    #endif /* STM32F10X_CL */

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0) {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08) {
        }
    }
    else {
		/* If HSE fails to start-up, the application will have wrong clock 
		configuration. User can add here some code to deal with this error */
    }
}

void EXTI0_IRQHandler() {
    // 进入停止模式后, HSE / HSI 时钟振荡器均关闭, 需要重新初始化
    SetSysClockTo72MHz();
    // 清除 EXTI 线路挂起位
    EXTI_ClearITPendingBit(EXTI_Line0);
}

```



### 15 STM32低功耗模式 - 待机模式

例程说明:

​	通过按键 PA1(低电平) 进入 待机STANDBY 模式, 通过 PA0(高电平) 上升沿唤醒

​	CPU 上电启动后 ->

​		LED 间隔 0.2s 闪烁, 当 PA1 引脚检测到低电平时, 进入 EXTI1 中断并进入待机模式(STANDBY), LED 不再闪烁;

​		当 PA0 检测到高电平时, CPU 被唤醒(需使能 PA0 的 WKUP 功能), LED 灯开始闪烁.



代码:

```c
#include <stm32f10x.h>

void Delay_us(unsigned long nCount);
void GPIOC_Configuration(void);
void PA1_EXTI1_Configuration(void);
void PA0_WKUP_Configuration(void);

int main(void) {
    
    SysTick_Configuration();
    GPIOC_Configuration();
    PA1_EXTI1_Configuration();
    
    PA0_WKUP_Configuration();	// 使能引脚(PA0)唤醒功能
    
    while(1) {
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        Delay_us(200000);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        Delay_us(200000);
    }
}

void EXTI1_IRQHandler() {
    if(SET == EXTI_GetITStatus(EXTI_Line1)) {	// 检查中断是否发生
        PWR_ClearFlag(PWR_FLAG_WU);	// 清除唤醒标志位
        PWR_EnterSTANDBYMode();	//  进入待机(STANDBY)模式
        // ??
        //EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

void PA0_WKUP_Configuration() {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	// 使能 PWR 时钟
    PWR_WakeUpPinCmd(ENABLE);	// 使能引脚(PA0)唤醒功能
}

void PA1_EXTI1_Configuration() {
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	// 外部中断 使能复用时钟
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 内部上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_EXTILineConfig(GPIO_PortSource_GPIOA, GPIO_PinSource1);	// 使能外部中断模式
}

void GPIOC_Configuration() {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

```



### 16 DMA

例程说明:

​	利用 DMA 将内存数据通过 USART 串口发送



​	注(待解决):

​		// 数据位 NCOUNT 值过大时(>=5), 串口助手不显示

代码:

```c
#include <stm32f10x.h>
#define NCOUNT 1

extern unsigned char arr[NCOUNT];

void Delay_us(unsigned long nCount);
void GPIOC_Configuration(void);
void USART1_Configuration(void);
void DMA1_Configuration(void);


int main(void) {
    
    unsigned char arr[NCOUNT];
    unsigned int i;
    
    SysTick_Configuration();
    GPIOC_Configuration();
    USART1_Configuration();
    DMA1_Configuration();
    
    for(i = 0; i < NCOUNT; i++)
        arr[i] = 'A';
    
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);	// 使能 USART 的 DMA 请求
    
    while(1) {
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        Delay_us(1000000);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        Delay_us(1000000);
    }
}

void DMA1_Configuration() {	// DMA 初始化配置	内存数据传输至外设
    DMA_InitTypeDef DMA_InitStructure;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	// 使能 DMA1 时钟
    
    DMA_InitStructure.DMA_PeripheralBaseAddr = (0x40013800 + 0x04);	// DMA 外设基地址: USART_DR
    DMA_InitStructure.DMA_MemoryBaseAddr = (unit32_t)arr;	// DMA 内存基地址: unit32_t, 需要强制类型转换
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	// 外设作为数据传输的目的地
    DMA_InitStructure.DMA_BufferSize = NCOUNT;	// DMA 缓存的大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	// 外设地址寄存器不变
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	// 内存地址寄存器增加 
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	// 外设数据宽度
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	// [内存]数据宽度
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	// 工作模式: Circular 循环缓存模式/ Normal 正常缓存模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;	// DMA 通道的优先级
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	// 是否使能内存到内存的传输
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);	// 完成 DMA1 配置, 通道值参阅 《STM32中文参考手册_V10》-> 10.3.7 表59
    
    DMA_Cmd(DMA1_Channel4, ENABLE);	// 使能通道
}
void USART1_Configuration() {
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);
	//USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);	// 所有初始化完成后, 使能 USART 的 DMA 请求
    USART_Cmd(USART1, ENABLE);
}

void GPIOC_Configuration() {
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

```



### 17 ADC 采集 CPU 温度

例程说明:

​	温度传感器

代码:

```c
#include <stm32f10x.h>
#defint V25 0x5
#define AVG_SLOPE 0x6EF

extern uint16_t ADC_ConvertVal;

void Delay_us(unsigned long nCount);
void GPIOC_Configuration(void);
void USART1_Configuration(void);
void ADC1_Configuration(void);


int main(void) {
    
    uint16_t ADC_ConvertVal;
    float Temperature;
    
    SysTick_Configuration();
    GPIOC_Configuration();
    USART1_Configuration();
    ADC1_Configuration();
    
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
    while(1) {
        Temperature = (((V25 - ADC_ConvertVal) / AVG_SLOPE) + 25);
        /*
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        Delay_us(1000000);
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        Delay_us(1000000);
        */
        printf("Temperature = %.2f\n", Temperature);        
    }
}
void ADC1_Configuration() {
    DMA_InitTypeDef DMA_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	// 使能 DMA1 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    
    DMA_InitStructure.DMA_PeripheralBaseAddr = (0x40012400 + 0x4C);	// DMA 外设基地址: ADC_DR
    DMA_InitStructure.DMA_MemoryBaseAddr = (unit32_t)&ADC_ConvertVal;	// DMA 内存数据地址: unit32_t, 需要强制类型转换
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	// 外设作为数据传输的来源
    DMA_InitStructure.DMA_BufferSize = 1;	// DMA 缓存的大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	// 外设地址寄存器不变
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	// 内存地址寄存器不变 
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_HalfWord;	// 外设数据宽度
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	// [内存]数据宽度
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	// 工作模式: Circular 循环缓存模式/ Normal 正常缓存模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;	// DMA 通道的优先级
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	// 是否使能内存到内存的传输
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);	// 完成 DMA1 配置, 通道值参阅 《STM32中文参考手册_V10》-> 10.3.7 表59
    DMA_Cmd(DMA1_Channel1, ENABLE);	// 使能通道
    
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	// ADC1 / ADC2 工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	// 扫描(多通道)模式 / 单次(单通道)模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	// 连续 / 单次模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// 由软件触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	// 数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);	// 设置 ADC 时钟, 由 PCLK 分频
    // 设置 ADC 通道, 采样周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_55Cycles5);	// 转换一次用时: 周期 12.5 + 55.5 = 68
																					// 频率 72 / 8 = 9 MHz
																					// 时间 t = 68 * (1 / 9 MHz) = 7.556 us
	ADC_TempSensorVrefintCmd(ENABLE);	// 使能温度传感器和内部参考电压的通道
	ADC_DMACmd(ADC1, ENABLE);	// 使能 ADC 的 DMA 请求
	ADC_Cmd(ADC1, ENABLE);	// 使能指定的 ADC
	
    // ADC 校准
	ADC_ResetCalibration(ADC1);	// 重置校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));	// ?? 获取重置校准寄存器的状态, 重置成功为 RESET
	ADC_StartCalibration(ADC1);	// 开始指定 ADC 的校准状态
	while(ADC_GetCalibrationStatus(ADC1));	// ?? 获取校准程序, RESET
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	// 使能 ADC 的软件转换启动功能
}

void USART1_Configuration() {
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}
int fputc(int c, FILE *fp) {
	while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TXE));
	USART_SendData(USART1, c);
	while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TC));
	
	return 0;
}
void GPIOC_Configuration() {
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

```



### 18 TIM2 定时器

例程说明:

​	利用 TIM2 实现 LED 间隔 500 ms 闪烁.

代码:

```c
#include <stm32f10x.h>

extern unsigned int Timer;

void GPIOC_Configuration(void);
void TIM2_BaseConfiguration(void);

int main(void) {
    
    unsigned int Timer;	// TIM2 进中断次数的计数值
    GPIOC_Configuration();
    TIM2_BaseConfiguration();
    
    // TIM 配置时已关闭时钟, 使用前重新开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);	// LED 亮
    while(1) {
        
    }
}

void TIM2_BaseConfiguration(void) {	// TIM 基本功能(定时)初始化配置, 1 ms 进入一次 TIM2 中断
    NVIC_InitTypeDef NVIC_InitStructure;	// ITM2 中断
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 0x3E7;	// 999 自动重装载寄存器周期值: 计数 999 + 1 = 1000 个
	TIM_TimeBaseStructure.TIM_Prescaler = 0x47;	// 72 预分频值: 72MHz 再进行分频	预分频值 71 + 1 = 72
												// 产生中断时间: t = T * nCount = ((1 / 72MHz) * 72) * 1000 = 1 ms
												// 内部会自 +1 被除数不能为 0
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 计数模式: 向上计数
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);	// 完成初始化配置
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	// 清除 TIM 待处理(更新)标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );·// 使能指定的中断
	
	TIM_Cmd(TIM2, ENABLE);	// 使能 TIM2 外设
	
	// 暂时关闭 TIM2 时钟, 使用前开启
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);
}
void TIM2_IRQHandler() {	// 根据 TIM2 配置, 1 ms 进入一次此中断
    if(SET == TIM_GetITStatus(TIM2, TIM_IT_Update)) {	// 判断中断是否发生
        Timer++;
        if(Timer == 500) {	// 计时 500 ms
            GPIOC->ODR ^= GPIO_Pin_13;	// GPIOC_13 引脚状态反转
            Timer = 0;
        }
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	// 清除中断标志位
    }
}

void GPIOC_Configuration() {
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 通用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

```



### 19 RTC 实时时钟

例程说明:

​	通过 UASRT1 显示 RTC 时钟时间.

​	RTC 初始化步骤:

​		设置寄存器 RCC_APB1ENR 的 PWREN 和 BKPEN 位, 使能电源和后备接口时钟;

​		设置寄存器 PWR_CR 的 DBP 位, 使能对后备寄存器和 RTC 的访问.

​		复位 RTC_PRL / RTC_ALR / RTC_CNT / RTC_DIV 寄存器

​		使能 LSE 外部振荡时钟, 32.768 kHz

​		等待 LSE 起振就绪

​		设置 RTC 时钟 -> LSE

​		使能 RTC 时钟, 开始工作

​		等待 RTC 寄存器写操作完成

​		等待寄存器[同步]标志位置 1

​		设置预分频值 -> 32768 

​		等待 RTC 寄存器写操作完成



代码:

```c
#include <stm32f10x.h>

#define leapyear(a) ((((a % 4) == 0) && ((a % 100) != 0)) || ((a % 400) == 0))	// 判断当前年份是不是闰年
#define days_in_year(i) (leapyear(i) ? 366 : 365)	// 判断当前年份有多少天

struct RTC_TIM {	// 定义时间结构体
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
};
extern unsigned int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};	// 定义月份的天数

void Delay_us(unsigned long nCount);
void USART1_Configuration(void);
int RTC_Configurtion(void);
void RTC_Display(u32 RTC_TimVal);
void USART1_Scanf(unsigned int *pt, unsigned int bits);
void Set_RTCTime(void);

int main(void) {
    
    unsigned int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned int flag;	// RTC 是否配置过标志位
    
    SysTick_Configuration();
    USART1_Configuration();
    flag = RTC_Configuration();	// 此前配置过 RTC 返回 1, 未配置过 RTC 返回 0(未断过电) 
    
    if(0 == flag) {	// flag == 0 说明此次运行时对 RTC 进行了重新初始化, [需要]按照当前实际时间对 RTC 进行赋值
        Set_RTCTime();	// 设置 RTC 计数值
    }
    
    while(1) {
        RTC_Display(RTC_GetCounter());	// 将获取的当前 RTC 计数值显示出来
        Delay_us(1000000);	// 1 s 显示一次
    }
}

// 返回值 == 1, 代表已经配置过 RTC, 则无需重新配置;
// 若返回值 == 0, 表示未配置过 RTC, 则需指定时间.
int RTC_Configuration() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	// 使能电源和后备接口时钟
	PWR_BackupAccessCmd(ENABLE);	// 使能对后备寄存器和 RTC 的访问
	
	if(0xA587 != BKP_ReadBackupRegister(BKP_DR1)){	// 判断备份数据寄存器值(-值不会被系统复位、电源复位、从待机模式唤醒所复位-)是否与当前值相等, 若相等, 说明前期已配置过 RTC, 不再进行配置, 返回值 1. 取值 0x0000 ~ 0xFFFF
		BKP_DeInit();	// 寄存器复位
						// 需仅第一次运行时初始化, 不断电时不初始化
		RCC_LSEConfig(RCC_LSE_ON);	// 设置使用外部晶振 LSE: 32.768 kHz
		while(RESET == RCC_GetFlagStatus(RCC_FLAG_LSERDY));	// 等待 LSE 晶振就绪
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);	// 选择 LSE 作为 RTC 时钟
		RCC_RTCCLKCmd(ENABLE);	// 使能 RTC 时钟
		RTC_WaitForLastTask();	// 等待最近一次对 RTC 寄存器的写操作完成
								// RTC->CRL 位5 为 1
		RTC_WaitForSynchro();	// 等待同步完成
								// RTC->CRL 位3 为 1
		RTC_SetPrescaler(32767);	// 设置 RTC 预分频值: [寄存器内部自加 1]	32768分频 = 32767 + 1
		RTC_WaitForLastTask();
		BKP_WriteBackupRegister(BKP_DR1, 0xA587);	// 将值写入备份数据寄存器, 下次运行时有此值, 说明前期已对 RTC 进行过配置, 此值 0xA587 可自定义
		
		return 0;
	}
	else
		return 1;
}
void RTC_Display(u32 RTC_TimVal) {	// 显示 RTC 时间
    struct RTC_TIM TIM;
    unsigned int days, hms;
    unsigned int i;
    
    days = (RTC_TimVal / (24 * 60 * 60)); // 整数的天数
    hms = RTC_TimVal % 86400;	// 剩余秒数
    
    TIM.hour = hms / 3600;	// 小时
    TIM.minute = ((hms % 3600) / 60);	// 分钟
    TIM.second = ((hms % 3600) % 60);	// 秒
    
    for(i = 1970; days >= days_in_year(i); i++) {
		days -= days_in_year(i);
	}
	TIM.year = i;	// 年
    
	if(leapyear(i))
		days_in_month[2] = 29;
	else
		days_in_month[2] = 28;
	
	for(i = 1; days >= days_in_month[i]; i++) {
		days -= days_in_month[i];
	}
	TIM.month = i;	// 月
	TIM.day = days + 1;	// 日!
	
	printf("%.4d-%.2d-%.2d %.2d:%.2d:%.2d\n", TIM.year, TIM.month, TIM.day, TIM.hour, TIM.minute, TIM.second);
}

void USART1_Scanf(unsigned int *pt, unsigned int bits) {
    unsigned int i = 0;
    unsigned int tmp[] = {0, 0, 0, 0};
    while(i < bits) {
        while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_RXNE));
        tmp[i++] = USART_ReceiveData(USART1);
    }
    if(4 == bits)
        *pt = (tmp[0] - '0') * 1000 + (tmp[1] - '0') * 100 + (tmp[2] - '0') * 10 + (tmp[3] - '0');
    //
    if(2 == bits)
        *pt = (tmp[0] - '0') * 10 + (tmp[1] - '0');
}
void Set_RTCTime() {	// 设置 RTC 系统时间
    struct RTC_TIM setTime;
    unsigned long i, timeVal = 0;
    // 重新设置时间提示
    printf("Please enter year:\n");
    USART1_Scanf(&setTime.year, 4);
    printf("Please enter month:\n");
    USART1_Scanf(&setTime.month, 2);
    printf("Please enter day:\n");
    USART1_Scanf(&setTime.day, 2);
    printf("Please enter hour:\n");
    USART1_Scanf(&setTime.hour, 2);
    printf("Please enter minute:\n");
    USART1_Scanf(&setTime.minute, 2);
    printf("Please enter second:\n");
    USART1_Scanf(&setTime.second, 2);
    // 转化为秒数
    for(i = 1970; i < setTime.year; i++) {
        timeVal += (days_in_year(i) * 86400);
    }
    if(leapyear(setTime.year))
		days_in_month[2] = 29;
	else
		days_in_month[2] = 28;
    for(i = 1; i < setTime.month; i++) {
        timeVal += (days_in_month[i] * 86400);
    }
    timeVal += (setTime.day - 1) * 86400;	// 当天时间不满一天
    timeVal += (setTime.hour * 3600 + setTime.minute * 60 + setTime.second);
        
    RTC_SetCounter(timeVal);	// 设置当前时间值(s) '1200000000 设置值'
}

void USART1_Configuration() {
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}
int fputc(int c, FILE *fp) {
	while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TXE));
	USART_SendData(USART1, c);
	while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TC));
	
	return 0;
}

```



### 20 矩阵(Matrix)按键

例程说明:

​	USART 返回对应按键值.

原理:

​	行列翻转.

​		S01		S05		S09		S13	PA4	[行1

​		S02		S06		S10		S14	PA5	行2

​		S03		S07		S11		S15	PA6	行3

​		S04		S08		S12		S16	PA7	行4]

​		PA0		PA1		PA2		PA3

​		[列1		列2		列3		列4]

流程:

​	PA0~PA3 配置内部上拉输入模式 / PA4~PA7 配置通用推挽输出->低电平;

​	PA4~PA7 配置内部上拉输入模式 / PA0~PA3 配置通用推挽输出->低电平;


​	PA0~PA3 读取到低电平, 有按键按下, 进行判断得到[列];

​	反转行列, PA4~PA7 读取到低电平, 有按键按下, 进行判断得到[行].

代码:

```c
#include <stdio.h>

void USART1_Configuration(void);
int Matrix_Key(void);

int main(void) {
    
    unsigned int Key_num;
    SysTick_Configuration();
    USART1_Configuration();
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// Matrix_Key() 函数需要频繁运行, 只在此处进行一次 GPIO 时钟使能
    
    while(1) {
        Key_num = Matrix_Key();	// 当有按键按下时, 返回对应的 Val 值, 无按键按键按下时返回 0
        if(0 != Key_num)
            printf("Key: %d\n", Key_num);
    }
}

int Matrix_Key() {
    unsigned int Key, Val;
    
    // 判断[列]值
	GPIO_InitTypeDef GPIO_InitStructure;
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, Bit_RESET);
	
	if((GPIOA->IDR & 0x0F) != 0x0F) {
		Delay_us(200);
		Key = (GPIOA->IDR &0x0F);
		if(Key != 0x0F) {
			switch(Key) {
				case 0x0E: Val = 1; break;
				case 0x0D: Val = 5; break;
				case 0x0B: Val = 9; break;
				case 0x07: Val = 13; break;
				default: break;
			}
		}
		else
			return 0;
		
        // 判断[行]值
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3, Bit_RESET);
		
		if((GPIOA->IDR & 0xF0) != 0xF0) {
			Delay_us(200);
			Key = (GPIOA->IDR & 0xF0);
			if(Key != 0xF0) {
				switch(Key) {
					case 0xE0: Val += 0; break;
					case 0xD0: Val += 1; break;
					case 0xB0: Val += 2; break;
					case 0x70: Val += 3; break;
					default: break;
				}
			}
			else
				return 0;
		}
		else
			return 0;
		
		while((GPIOA->IDR & 0xF0) != 0xF0);
		return Val;
	}
	else
		return 0;
}

void USART1_Configuration() {
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}
int fputc(int c, FILE *fp) {
	while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TXE));
	USART_SendData(USART1, c);
	while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TC));
	
	return 0;
}

```



### 21 PWM 配置

例程说明:

​	PWM 占空比: 高电平时间 / 周期

​	1. 利用 PWM 实现呼吸灯

​	2. 利用 PWM 控制舵机



有关参数 TIM_OCMode、TIM_OCPolarity:

​	PWM1 模式:

​		TIM_OCPolarity_High:

​			TIMx_CNT < TIMx_CCR 输出高电平

​			TIMx_CNT > TIMx_CCR 输出低电平

​		TIM_OCPolarity_Low:

​			TIMx_CNT < TIMx_CCR 输出低电平

​			TIMx_CNT > TIMx_CCR 输出高电平

​	PWM2 模式:

​		TIM_OCPolarity_High:

​			TIMx_CNT < TIMx_CCR 输出低电平

​			TIMx_CNT > TIMx_CCR 输出高电平

​		TIM_OCPolarity_Low:

​			TIMx_CNT < TIMx_CCR 输出高电平

​			TIMx_CNT > TIMx_CCR 输出低电平



代码:

```c
#include <stm32f10x.h>
#define NCOUNT 20000	// 依据 .TIM_Period = 0x7CF

void TIM2_PWM_Configuration(void);
extern unsigned long TimingDelay;

int main(void) {
    
    unsigned int i;
    
    SysTick_Configuration();
    TIM2_PWM_Configuration();
    
    while(1) {
        // LED 呼吸灯
        for(i = 0; i < NCOUNT; i++) {
            TIM_SetCompare2(TIM2, i);	// 改变占空比
            Delay_us(50);
        }
        for(i = NCOUNT; i > 0; i--) {
            TIM_SetCounter2(TIM2, i);
            Delay_us(50);
        }
        // 舵机控制
        TIM_SetCompare2(TIM2, 500);	// 0.5ms - 0°
		Delay_us(1000000);
		TIM_SetCompare2(TIM2, 1000);	// 1ms - 45°
		Delay_us(1000000);
		TIM_SetCompare2(TIM2, 1500);	// 1.5ms - 90°
		Delay_us(1000000);
		TIM_SetCompare2(TIM2, 2000);	// 2ms - 135°
		Delay_us(1000000);
		TIM_SetCompare2(TIM2, 2500);	// 2.5ms - 180°
		Delay_us(1000000);
        // 舵机循环
        for(i = 500; i <= 2500; i++)
		{
			TIM_SetCompare2(TIM2, i);
			Delay_us(500);
		}
		for(i = 2500; i >= 500; i--)
		{
			TIM_SetCompare2(TIM2, i);
			Delay_us(500);
		}
    }
}

void TIM2_PWM_Configuration() {
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);	// PA1 复用功能 -> TIM2_CH2
    
    TIM_TimeBaseStructure.TIM_Period = 0x4E1F;
    TIM_TimeBaseStructure.TIM_Prescaler = 0x47;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    //TIM_OCInitStructure.TIM_Pulse = 0x3FFF;	// 捕获比较寄存器
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);	// 定时器2 通道2
    
    TIM_Cmd(TIM2, ENABLE);
}

```



### 22 无源蜂鸣器

例程说明:

代码:

```c
#include <stm32f10x.h>

int main(void)
{
    SysTick_Configuration();
    
    TIM4_PWM_Configuration();
    
    while(1)
    {
        //
    }
}

void TIM4_PWM_Configuration()
{
    //
}

```



### 23 超声波传感器

### 24 自定义 USART 数据格式

### 25 SPI 通信协议

例程说明:

代码:



### 26 定时器输入捕获

### 27 数码管

### 28 设置RTC系统时间

例程说明:

​	19 RTC 实时时钟

代码:

```c
#include <stm32f10x.h>

int main(void) {
    
    SysTick_Configuration();
    
    while(1) {
        //
    }
}

```



### 29 LCD1602

### 30 DS18B20

### 31 I2C_EEPROM

### 32 ULN2003_28BYJ-48步进电机

例程说明：

ULN2003 + 28BYJ-48

接线表：

​	STM32			ULN2003

​	PA4	<---->	IN1

​	PA5	<---->	IN2

​	PA6	<---->	IN3

​	PA7	<---->	IN4

通电次序：

​	正转(逆)：

​		A-AB-B-BC-C-CD-D-DA

​	反转(顺)：

​		A-AD-D-CD-C-CB-B-BA

参数：

| 电压 DC.V | 电阻 | 步距角    | 减速比 | 牵入转矩 | 自定位转矩 | 空载牵入频率 | 空载牵出频率 | 绝缘电阻 | 绝缘介电强度 | 温升 | 噪音 |
| --------- | ---- | --------- | ------ | -------- | ---------- | ------------ | ------------ | -------- | ------------ | ---- | ---- |
| 5         | 50Ω  | 5.625°/64 | 1/64   | ≥40      | ≥34.3      | ＞500        | ＞900        |          |              |      |      |

转角说明：

​	64个脉冲转360°，1个脉冲转360°/64=5.625°，即1个周期励磁顺序转动5.625°，1个周期励磁分为8步，则1步转动角度5.625°/8=0.703125°，综上，当励磁改变1次，对应电机转动0.703125°。

​	当需要定角度转动时，用需要转动的角度/0.703125°即得需要改变励磁的次数。

​	如当需要转动360°时，需要改变的励磁次数=360°/0.703125°=512次？

代码：

```c
#include <stm32f10x.h>

#define STEPPER_ANGLE 0.703125
enum dir {Pos, Neg};	// 枚举类型 Pos = 0, Neg = 1
#define IN1_HIGH	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET)
#define IN1_LOW		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET)
#define IN2_HIGH	GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET)
#define IN2_LOW		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET)
#define IN3_HIGH	GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET)
#define IN3_LOW		GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_RESET)
#define IN4_HIGH	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET)
#define IN4_LOW		GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_RESET)

void ULN2003_Configuration(void);
void Stepper(unsigned int dir, unsigned int speed);

int main(void)
{
    SysTick_Configuration();
    ULN2003_Configuration();
    
    while(1)
    {
        // 正转一个周期, 频率1000
        Stepper(Neg, 1000);
        // 正转, 角度90°, 频率1000
        Angle_Control(Neg, 90, 1000);
    }
}

void ULN2003_Configuration()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, Bit_RESET);
}

void Stepper(unsigned int dir, unsigned int speed)
{
    if(dir == Pos)
    {
        //正转
        //1
		IN1_HIGH; IN2_LOW; IN3_LOW; IN4_LOW;
		Delay_us(speed);
		//2
		IN1_HIGH; IN2_HIGH; IN3_LOW; IN4_LOW;
		Delay_us(speed);
		//3
		IN1_LOW; IN2_HIGH; IN3_LOW; IN4_LOW;
		Delay_us(speed);
		//4
		IN1_LOW; IN2_HIGH; IN3_HIGH; IN4_LOW;
		Delay_us(speed);
		//5
		IN1_LOW; IN2_LOW;  IN3_HIGH; IN4_LOW;
		Delay_us(speed);
		//6
		IN1_LOW; IN2_LOW; IN3_HIGH; IN4_HIGH;
		Delay_us(speed);
		//7
		IN1_LOW; IN2_LOW; IN3_LOW; IN4_HIGH;
		Delay_us(speed);
		//8
		IN1_HIGH; IN2_LOW; IN3_LOW; IN4_HIGH;
		Delay_us(speed);
    }
    else
    {
        //反转
        //1
		IN1_HIGH; IN2_LOW; IN3_LOW; IN4_HIGH;
		Delay_us(speed);
		//2
		IN1_LOW; IN2_LOW; IN3_LOW; IN4_HIGH;
		Delay_us(speed);
		//3
		IN1_LOW; IN2_LOW; IN3_HIGH; IN4_HIGH;
		Delay_us(speed);
		//4
		IN1_LOW; IN2_LOW; IN3_HIGH; IN4_LOW;
		Delay_us(speed);
		//5
		IN1_LOW; IN2_HIGH; IN3_HIGH; IN4_LOW;
		Delay_us(speed);
		//6
		IN1_LOW; IN2_HIGH; IN3_LOW; IN4_LOW;
		Delay_us(speed);
		//7
		IN1_HIGH; IN2_HIGH; IN3_LOW; IN4_LOW;
		Delay_us(speed);
		//8
		IN1_HIGH; IN2_LOW; IN3_LOW; IN4_LOW;
		Delay_us(speed);
    }
}

void Angle_Control(unsigned int dir, double angle, unsigned int speed)
{
    unsigned int i;
    for(i = 0; i < angle / STEPPER_ANGLE; i++)
        Stepper(dir, speed);
}

```

### 33 TCS3200 颜色识别

### 34 DHT11 温湿度传感器

例程说明:

DHT11

接线表:

​	STM32		DHT11

​	PA0



代码:

```C
#include<stm32f10x.h>

int main()
{
    SysTick_Configuration();
    
    
    while(1)
    {
        //
    }
}

```



### 35 OLED_0.96

### 36 直流有刷减速电机

### 37 数模转换MCP4725

### 38 NRF24L01

### 39 摇杆



