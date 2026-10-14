/*
 * ring_buffer.h
 *
 *  Created on: Oct 4, 2026
 *      Author: junaidahmadmir
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f407xx.h"

#define RING_BUFFER_SIZE 64  /* Must be a power of 2 */

typedef int32_t q16_t;

#define Q16_SHIFT 16
#define Q16_ONE   (1 << Q16_SHIFT)

/* Conversions */
q16_t float_to_q16(float f);
float q16_to_float(q16_t q);
q16_t int_to_q16(int32_t i);
int32_t q16_to_int(q16_t q);

/* Arithmetic */
q16_t q16_add(q16_t a, q16_t b);
q16_t q16_sub(q16_t a, q16_t b);
q16_t q16_mul(q16_t a, q16_t b);
q16_t q16_div(q16_t a, q16_t b);

/* DSP Kernel: Exponential Moving Average */
q16_t q16_ema_filter(q16_t current_sample, q16_t prev_output, q16_t alpha);


typedef struct {
    uint16_t buffer[RING_BUFFER_SIZE];
    volatile size_t head;
    volatile size_t tail;
} RingBuffer_t;

void ring_buffer_init(RingBuffer_t *rb);
bool ring_buffer_push(RingBuffer_t *rb, uint16_t byte);
bool ring_buffer_peek(const RingBuffer_t *rb,size_t index_offset, uint16_t *byte);
bool ring_buffer_pop(RingBuffer_t *rb, uint16_t *byte);
bool ring_buffer_is_empty(const RingBuffer_t *rb);
bool ring_buffer_is_full(const RingBuffer_t *rb);
size_t ring_buffer_available(const RingBuffer_t *rb);


#endif /* INC_RING_BUFFER_H_ */
