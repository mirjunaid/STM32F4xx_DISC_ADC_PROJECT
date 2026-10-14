/*
 * ADC.h
 *
 *  Created on: Sep 29, 2026
 *      Author: junaidahmadmir
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f407xx.h"

#define GPIOAEN         (1U << 0)
#define GPIODEN         (1U << 3)
#define ADC1EN          (1U << 8)

#define ADC_CH1         1U          // Channel 1 on PA1
#define ADC_SEQ_LEN1    0x00        // 1 conversion in sequence (bits [23:20] = 0000)

#define CR2_ADCON       (1U << 0)   // Enable ADC
#define CR2_CONT_CONV   (1U << 1)   // Continuous conversion mode
#define CR2_SWST        (1U << 30)  // Start conversion
#define SR_EOC          (1U << 1)   // End of conversion flag

void adc_init(void);
void ADC_conversion(void);
uint16_t ADC_read(void);


#endif /* INC_ADC_H_ */
