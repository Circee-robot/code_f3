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
 * Prescale 64000000 Hz system clock by 64 = 1000000 Hz.
 */
#define PWM_PRESCALE	(64)

/**
 * We need a 50 Hz period (1000 / 20ms = 50), thus divide 100000 by 50 = 20000 (us).
 */
#define PWM_PERIOD		(20000)


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

#define MOTOR_A_GPIO_RCC_DIR1		RCC_GPIOF
#define MOTOR_A_PORT_DIR1			GPIOF
#define MOTOR_A_PIN_DIR1			GPIO0

#define MOTOR_A_GPIO_RCC_DIR2		RCC_GPIOF
#define MOTOR_A_PORT_DIR2			GPIOF
#define MOTOR_A_PIN_DIR2			GPIO1

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

#define MOTOR_B_GPIO_RCC_DIR1		RCC_GPIOA
#define MOTOR_B_PORT_DIR1			GPIOA
#define MOTOR_B_PIN_DIR1			GPIO3

#define MOTOR_B_GPIO_RCC_DIR2		RCC_GPIOA
#define MOTOR_B_PORT_DIR2			GPIOA
#define MOTOR_B_PIN_DIR2			GPIO4

#define MOTOR_B_INVERT_DIR (0)
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
enum motor_state {STOP, FREE, FORWARD, BACKWARD};


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
