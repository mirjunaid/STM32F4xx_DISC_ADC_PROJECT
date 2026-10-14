/*
 * telemetry.c
 *
 *  Created on: Oct 4, 2026
 *      Author: junaidahmadmir
 */

#include "telemetry.h"
#include "ring_buffer.h"
#include "systick.h"


static uint64_t adc_sum = 0;
static uint32_t sample_count = 0;
static uint32_t last_window_time = 0;
static uint32_t window_period = 600000;

RingBuffer_t adc_rb;


void telemetry_init(uint32_t window_duration)
{
	window_period = window_duration;
	adc_sum = 0;
	sample_count = 0;
	last_window_time = 0;
	ring_buffer_init(&adc_rb);
}

void telemetry_feed_sample(uint16_t raw_sample)
{
	adc_sum += raw_sample;
	sample_count++;
}

void telemetry_process(void)
{
	// Directly pull the current time hardware tick count
	uint32_t now = get_system_ticks();


	if((now - last_window_time) >= window_period)
	{
		if(sample_count > 0)
		{
			uint16_t average_temp = (uint16_t)(adc_sum / sample_count);
			ring_buffer_push(&adc_rb, average_temp);

			adc_sum = 0;
			sample_count = 0;
		}
		last_window_time = now;
	}
}
