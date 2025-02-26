/**
 * @file
 *
 * This file is part of circee robot
 *
 * @brief This implements the regulation loops
 *
 * @date  10/2024
 *
 * Licence :
 *
 * Team circee
 * @author NPXav Benano Kit
 */

#pragma once
#include "clock.h"
#include "motor.h"
#include "encoder.h"

/**
 * Motor specific config structure for the PID
 */
typedef struct _config {
    enum motor_sel motor_sel;
    enum encoder_sel encoder_sel;
    float Kp;
    float Ki;
    float Kd;
    float imax;
} pid_config;

/**
 * Values of both motors' PIDs
 */
# define KP_A (1.3)
# define KI_A (0.2)
# define KD_A (25)
# define KP_B (1.3)
# define KI_B (0.2)
# define KD_B (25)

# define IMAX (100)

# define MEASURE_PERIOD_MS  (5)

/**
 * Contains motor specific PID loop state
 */
typedef struct _state {
    float directive_tick;
    int encoder_tick_prev;
    float last_error;
    float error_sum;
    float last_pid_output;
    int pos_tick;
} pid_state;
static const pid_state EMPTY_STATE;
/**
 * @brief To be called regularly, will try to follow directive set in
 * state enum
 *
 * @param config Motor specific config coefficients
 * @param state Motor specific state (last error, integrated error..)
 */
void update_motor(pid_config config, pid_state * state);
/**
 * @brief Computes PID from error
 *
 * @param error Error in
 * @param value value is between 0 and 255
 * @param state Motor config between STOP FREE FORWARD BACKWARD
 */
float pid(pid_config config, pid_state * state, float error);
/**
 * @brief This function pilots the motor_sel (MOTOR_A or MOTOR_B) with a value between -100(backward full speed) and +100 (forward full speed). The forward direction depends on the sign of MOTOR_X_INVER_DIR.
 *
 * @param state
 */
void set_directive(pid_state * state, float directive);
