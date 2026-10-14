/*
 * telemetry.h
 *
 *  Created on: Oct 4, 2026
 *      Author: junaidahmadmir
 */

#ifndef INC_TELEMETRY_H_
#define INC_TELEMETRY_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f407xx.h"

void telemetry_init(uint32_t window_duration);
void telemetry_feed_sample(uint16_t raw_sample);
void telemetry_process(void);


#endif /* INC_TELEMETRY_H_ */
