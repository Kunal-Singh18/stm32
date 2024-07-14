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

void pf3_adc_init(void);
uint32_t adc_read(void);
void start_conversion(void);

#endif /* ADC_H_ */
