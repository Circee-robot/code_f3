#pragma once
#include <libopencm3/stm32/timer.h>
#include <stdbool.h>

#include "timer.h"
#include "gpio.h"

#define US_TRIGGER_TIM_RCC RCC_TIM2
#define US_TRIGGER_TIM TIM2
#define US_TRIGGER_NVIC NVIC_TIM2_IRQ

#define US_TRIGGER_PRESCALER_TIM (64)
#define US_TRIGGER_PERIOD_TIM (250000)

#define US_TRIGGER_RISE_VALUE (1000)
#define US_TRIGGER_FALL_VALUE (1010)

#define US_TRIGGER_GPIO_RCC			RCC_GPIOB
#define US_TRIGGER_PORT				GPIOB
#define US_TRIGGER_PIN				GPIO0

#define US_ECHO_TIM_RCC RCC_TIM16
#define US_ECHO_TIM TIM16

#define US_ECHO_PRESCALER_TIM (64)
#define US_ECHO_PERIOD_TIM (100000)

#define US_ECHO_GPIO_RCC			RCC_GPIOB
#define US_ECHO_GPIO_AF             GPIO_AF1
#define US_ECHO_PORT				GPIOB
#define US_ECHO_PIN				    GPIO4

/**
 * @brief This function initializes the timers (including the timer output comparator) and GPIOs to pilot US trigger
 *
 */
void trigger_setup();

/**
 * @brief This function initializes the timers for input capture and GPIOs to pilot US ECHO
 *
 */
void echo_setup();

void tim15_isr();

