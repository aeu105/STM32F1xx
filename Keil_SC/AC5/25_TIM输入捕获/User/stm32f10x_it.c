/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    20-September-2021
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2011 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_systick.h"

unsigned int High_Val = 0;
unsigned char Read_High_Complete_Flag = 0;
static unsigned int Period = 0;


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void) {
	
	if(0 != TimingDelay)
		TimingDelay--;
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

void TIM3_IRQHandler(void) {
	
	static unsigned char High_Flag = 0;
	
	// 计数溢出
	if(SET == TIM_GetFlagStatus(TIM3, TIM_FLAG_Update)) {
		
		if(High_Flag == 1)
			Period++;
	}
	
	if(Read_High_Complete_Flag == 0) {	// 等 main() 函数读取 High_Val 值结束
		
		// 判断是否产生电平跳变中断
		if(SET == TIM_GetITStatus(TIM3, TIM_IT_CC1)) {
			
			if(High_Flag == 0) {	// 第一次跳变(上升沿)进中断
				
				// 计时开始
				TIM_SetCounter(TIM3, 0);
				High_Flag = 1;
				High_Val = 0;
				// 改变极性
				TIM_OC1PolarityConfig(TIM3, TIM_OCPolarity_Low);
			}
			else {	// (下降沿)进中断
				
				High_Val = (Period * 65536) + TIM_GetCounter(TIM3);
				Period = 0;
				TIM_OC1PolarityConfig(TIM3, TIM_OCPolarity_High);
				High_Flag = 0;
				Read_High_Complete_Flag = 1;
			}
		}
	}
	
	// 清除中断标志位
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1 | TIM_FLAG_Update);
}
