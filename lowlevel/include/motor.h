/**
 * @file
 *
 * This file is part of cdfr2020BaseRoulanteRework
 *
 * @brief This implements the functions required to pilot the propulsion motors of the robot
 *
 * @date  06/2020
 *
 * Licence :
 *
 * Robotronik Phelma
 * @author NPXav Benano Trukbidule
*/

#pragma once
#include <libopencm3/stm32/timer.h>

#include "timer.h"
#include "gpio.h"

/**
 * FIXME: update comment
 * Prescale 64000000 Hz system clock by 64 = 1000000 Hz.
 * We count from 0 so -1
 */
#define PWM_PRESCALE	(1)

/**
 * FIXME:UPDATE COMMENT
 * We need a 50 Hz period (1000 / 20ms = 50), thus divide 100000 by 50 = 20000 (us).
 * We count from 0 so -1
 */
#define PWM_PERIOD		(255*100)


/**
 * @defgroup MOTOR_TIM motor_tim
 * @{
 * @brief Internal timer used to pilot the motors
 *
 * Two channels are used for the MOTOR_A and MOTOR_B
 */
#define MOTOR_TIM_RCC				RCC_TIM1
#define MOTOR_TIM					TIM1
/** @} */

/**
 * @defgroup MOTOR_A motor_a
 * @{
 * @brief Definition for the MOTOR_A
 *
 * EN stands for enable (output of the PWM signal) \n
 * We use OC_ID to select a specific channel of the output comparator as a PWM_output\n
 * DIR stands for direction (boolean value) \n
 * INIT_DIR is the initial direction of the motor
 * INVERT_DIR allows to define the forward direction in motor_set (must be 1 or -1)
 */
#define MOTOR_A_GPIO_RCC_EN			RCC_GPIOA
#define MOTOR_A_PORT_EN				GPIOA
#define MOTOR_A_PIN_EN				GPIO8

#define MOTOR_A_AF					GPIO_AF6
#define MOTOR_A_OC_ID				TIM_OC1
#define MOTOR_A_OC_MODE				TIM_OCM_PWM1

#define MOTOR_A_GPIO_RCC_DIR		RCC_GPIOF
#define MOTOR_A_PORT_DIR			GPIOF
#define MOTOR_A_PIN_DIR			    GPIO1

#define MOTOR_A_INVERT_DIR (0)
/** @} */

/**
 * @defgroup MOTOR_B motor_b
 * @{
 * @brief Definition for the MOTOR_B
 *
 * EN stands for enable (output of the PWM signal) \n
 * We use OC_ID to select a specific channel of the output comparator as a PWM_output\n
 * DIR stands for direction (boolean value) \n
 * INIT_DIR is the initial direction of the motor
 * INVERT_DIR allows to define the forward direction in motor_set (must be 1 or -1)
 */
#define MOTOR_B_GPIO_RCC_EN			RCC_GPIOA
#define MOTOR_B_PORT_EN				GPIOA
#define MOTOR_B_PIN_EN				GPIO9

#define MOTOR_B_AF					GPIO_AF6
#define MOTOR_B_OC_ID				TIM_OC2
#define MOTOR_B_OC_MODE				TIM_OCM_PWM1

#define MOTOR_B_GPIO_RCC_DIR		RCC_GPIOA
#define MOTOR_B_PORT_DIR			GPIOA
#define MOTOR_B_PIN_DIR	    		GPIO3

#define MOTOR_B_INVERT_DIR (1)
/** @} */


/**
 * @defgroup MOTOR_EEP motor_eep
 * @{
 * @brief Sleep signal for H brigdge to free run the motors
 */
#define MOTOR_GPIO_RCC_EEP			RCC_GPIOA
#define MOTOR_PORT_EEP				GPIOA
#define MOTOR_PIN_EEP				GPIO4
/** @} */

/**
 * @brief enum of the two motors used to identify them in some functions (like function motor_set)
 *
 */
enum motor_sel {MOTOR_A, MOTOR_B};

/**
 * @brief enum of the possible motor states
 *
 */
enum motor_state {STOP, FORWARD, BACKWARD};


/**
 * @brief This function initializes the timers (including the timer output comparator) and GPIOs to pilot by PWM the propulsion motors + the GPIOs for the direction
 *
 */
void motor_setup();

/**
 * @brief This function pilots the sel (MOTOR_A or MOTOR_B) with a value between -100(backward full speed) and +100 (forward full speed). The forward direction depends on the sign of MOTOR_X_INVER_DIR.
 *
 * @param sel The motor that will be piloted (eg MOTOR_A)
 * @param value value is between 0 and 255
 * @param state Motor config between STOP FREE FORWARD BACKWARD
 */
void motor_set(enum motor_sel sel, uint8_t value, enum motor_state state);

void motor_sleep();