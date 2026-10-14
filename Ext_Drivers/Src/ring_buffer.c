/*
 * ring_buffer.c
 *
 *  Created on: Oct 4, 2026
 *      Author: junaidahmadmir
 */



#include "ring_buffer.h"

// Convert Float to Q16
q16_t float_to_q16(float f)
{
	q16_t q_fixed = (int32_t)(f * 65536.0f);
	return q_fixed;
}

// Convert Q16 to float
float q16_to_float(q16_t q)
{
	float f = (float)(q / 65536.0f);
	return f;
}

// Convert int to Q16
q16_t int_to_q16(int32_t i)
{
	return (i << Q16_SHIFT);
}

// Convert Q16 to int
int32_t q16_to_int(q16_t q)
{
	return (q >> Q16_SHIFT);
}

/* Arithmetic */

// Add two Q16 types
q16_t q16_add(q16_t a, q16_t b)
{
	return a + b;
}

// Subtract two Q16 types
q16_t q16_sub(q16_t a, q16_t b)
{
	return a - b;
}

// Multiply two Q16 types
q16_t q16_mul(q16_t a, q16_t b)
{
	q16_t result = (int32_t)((((int64_t)a) * b) >> 16);
	return result;
}

// Divide two Q16 types
q16_t q16_div(q16_t a, q16_t b)
{
	q16_t result = (int32_t)(((((int64_t)a) << 16) / b));
	return result;
}

q16_t q16_ema_filter(q16_t current_sample, q16_t prev_output, q16_t alpha)
{
	q16_t diff = current_sample - prev_output;
	return prev_output + q16_mul(alpha, diff);
}
// Initialize the buffer
void ring_buffer_init(RingBuffer_t *rb)
{
	rb -> head = 0;
	rb -> tail = 0;
}

// Function for writing data into the buffer
bool ring_buffer_push(RingBuffer_t *rb, uint16_t byte)
{
	if(((rb -> head + 1) & (RING_BUFFER_SIZE - 1)) == rb -> tail)
		return false;  // Buffer is full

	rb -> buffer[rb -> head] = byte;
	__atomic_signal_fence(__ATOMIC_RELEASE);    // Ensures data is committed before head updates
	rb -> head = (rb -> head + 1) & (RING_BUFFER_SIZE - 1);
	return true;
}

// Function for Reading data from the buffer
bool ring_buffer_pop(RingBuffer_t *rb, uint16_t *byte)
{
	if(rb -> head == rb -> tail)
		return false; // Buffer is empty nothing to read

	*byte = rb -> buffer[rb -> tail];
	__atomic_signal_fence(__ATOMIC_ACQUIRE);
	rb -> tail = (rb -> tail + 1) & (RING_BUFFER_SIZE -1);
	return true;
}

