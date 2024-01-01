#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__


#include <stm32f10x.h>

// 1.43 V
#define V25 ((1.43 * 0xFFF) / 3.3)	// 0x6EF	// ((1.43 * 0xFFF) / 3.3)

// 4.3 mV/¡æ	0.0043 V
#define AVG_SLOPE ((0.0043 * 0xFFF) / 3.3)	// 0x5	// ((0.0043 * 0xFFF) / 3.3)

extern uint16_t ADC_ConvertVal;

void ADC1_Configuration(void);


#endif	/* __BSP_ADC_H__ */
