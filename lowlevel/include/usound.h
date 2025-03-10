#pragma once
#include <libopencm3/stm32/timer.h>
#include <stdbool.h>

#include "timer.h"
#include "gpio.h"

#define US_TRIGGER_TIM_RCC RCC_TIM17
#define US_TRIGGER_TIM TIM17
#define US_TRIGGER_NVIC NVIC_TIM1_TRG_COM_TIM17_IRQ

#define US_TRIGGER_PRESCALER_TIM (64)
#define US_TRIGGER_PERIOD_TIM (500000)

#define US_TRIGGER_RISE_VALUE (1000)
#define US_TRIGGER_FALL_VALUE (1009)

#define US_TRIGGER_GPIO_RCC			RCC_GPIOB
#define US_TRIGGER_PORT				GPIOB
#define US_TRIGGER_PIN				GPIO5

#define US_ECHO_TIM_RCC RCC_TIM16
#define US_ECHO_TIM TIM16
#define US_ECHO_NVIC NVIC_TIM1_UP_TIM16_IRQ

#define US_ECHO_PRESCALER_TIM (64)
#define US_ECHO_PERIOD_TIM (200000)

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



extern volatile bool measurement_started;
extern volatile int measurement_us;
