/*
 * adc.h
 *
 *  Created on: Oct 8, 2026
 *      Author: Admin
 */

#ifndef ADC_H_
#define ADC_H_
#include "stm32f4xx.h"
#include <stdint.h>

void pa1_adc_init();
void start_conversion();
uint32_t adc_read();

#endif /* ADC_H_ */
