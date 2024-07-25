/*
 * adc.h
 *
 *  Created on: Jul 9, 2024
 *      Author: kunal
 */


#ifndef ADC_H_
#define ADC_H_

#include  "stm32f4xx.h"
#include <stdint.h>

#define SR_EOC           (1U<<1)

void pf3_adc_init(void);
uint32_t adc_read(void);
void start_conversion(void);
void pf3_adc_interrupt_init(void);

#endif /* ADC_H_ */
