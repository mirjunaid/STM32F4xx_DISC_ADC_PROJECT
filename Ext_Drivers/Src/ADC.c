/*
 * ADC.c
 *
 *  Created on: Sep 29, 2026
 *      Author: junaidahmadmir
 */
#include "ADC.h"

void adc_init(void)
{
    /* 1. Enable GPIOA and GPIOD Clocks on AHB1 */
    RCC->AHB1ENR |= (1U << 0); // GPIOAEN
    RCC->AHB1ENR |= (1U << 3); // GPIODEN

    /* 2. Configure PD12 as General Purpose Output (bits 25:24 = 01) */
    GPIOD->MODER &= ~(3U << 24);
    GPIOD->MODER |=  (1U << 24);

    /* 2. Configure PD13 as General Purpose Output (bits 27:26 = 01) */
    GPIOD->MODER &= ~(1U << 26);
    GPIOD->MODER |= (1U << 27);

    /* 3. Configure PA1 as Analog Mode (bits 3:2 = 11) */
    GPIOA->MODER |= (3U << 2);

    /* 4. Enable ADC1 Clock on APB2 */
    RCC->APB2ENR |= (1U << 8);

    /* 5. Set Channel 1 (PA1) in Sequence Register 3 */
    ADC1->SQR3 = 1U;

    /* 6. 1 Conversion in regular sequence */
    ADC1->SQR1 = 0U;

    /* 7. Power on the ADC module */
    ADC1->CR2 |= (1U << 0); // ADON

    /* 8. Mandatory ADC stabilization delay (~10 microseconds) */
    for (volatile int i = 0; i < 10000; i++) {
        __asm("nop");
    }
}

void ADC_conversion(void)
{
    /* Continuous conversion mode + Software Start */
    ADC1->CR2 |= (1U << 1);  // CONT
    ADC1->CR2 |= (1U << 30); // SWSTART
}

uint16_t ADC_read(void)
{
    /* Wait for End of Conversion flag */
    while (!(ADC1->SR & (1U << 1)));

    /* Reading DR automatically clears the EOC flag */
    return ADC1->DR;
}


