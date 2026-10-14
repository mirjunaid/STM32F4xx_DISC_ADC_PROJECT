/*
 * systick.h
 *
 *  Created on: Oct 4, 2026
 *      Author: junaidahmadmir
 */

#ifndef INC_SYSTICK_H_
#define INC_SYSTICK_H_

#include "stm32f407xx.h"
#include <stdint.h>

void systick_init_ms(uint32_t cpu_freq_hz);
uint32_t get_system_ticks(void);
void systick_delay(uint32_t period);


#endif /* INC_SYSTICK_H_ */
