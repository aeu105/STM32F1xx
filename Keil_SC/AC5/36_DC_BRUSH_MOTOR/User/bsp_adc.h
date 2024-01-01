#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__


#include <stm32f10x.h>

#define ADC_DR (0x40012400 + 0x4C)


extern uint16_t ADC_ConvertVal;


void ADC1_CH6_Configuration(void);


#endif	/* __BSP_ADC_H__ */
