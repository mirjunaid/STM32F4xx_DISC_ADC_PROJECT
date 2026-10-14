/*
 * systick.c
 *
 *  Created on: Oct 4, 2026
 *      Author: junaidahmadmir
 */
#include "systick.h"

#define SYSTICK_CTRL_ENABLE		(1U << 0)    // Enable counter
#define SYSTICK_CTRL_TICKINT	(1U << 1)   // Enable systick interrupt
#define SYSTICK_CTRL_CLKSOURCE	(1U << 2)   // 1 = preocessor clock(AHB), 0 = AHB / 8

static volatile uint32_t g_system_ticks = 0;

void systick_init_ms(uint32_t cpu_freq_hz)
{
	// Load the value for 1ms (CPU_FREQ / 1000) - 1
	SysTick -> LOAD = (cpu_freq_hz / 1000) - 1U;

	//Clear current value register
	SysTick -> VAL = 0U;

	// Enable SysTick, enable interrupt,select internal processsor clock
	SysTick -> CTRL = SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_TICKINT | SYSTICK_CTRL_CLKSOURCE;
}

uint32_t get_system_ticks(void)
{
	return g_system_ticks;
}

void systick_delay(uint32_t period)
{
	uint32_t start_time = g_system_ticks;
	while((g_system_ticks - start_time) < period)
	{
		// wait
	}
}

// Vector table ISR Name
void SysTick_Handler(void)
{
	g_system_ticks++;
}

