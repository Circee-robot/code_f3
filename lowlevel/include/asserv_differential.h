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
 * Values of both motors' PIDs
 */

# define KP_DELTA (4)
# define KI_DELTA (0.1)
# define KD_DELTA (3.5)

# define KP_THETA (4)
# define KI_THETA (0.1)
# define KD_THETA (3.5)

# define IMAX (1000)

# define MEASURE_PERIOD_MS  (5)

/**
 * Contains motor specific PID loop state
 */
typedef struct _state_diff {
    float directive_value;
    float last_error;
    float error_sum;
    float last_pid_output;
    int pos_value;
} pid_state_diff;
static const pid_state_diff EMPTY_STATE;

typedef struct _encoder_state {
    int prev_A;
    int prev_B;
} encoder_state;


/**
 * @brief To be called regularly, will try to follow directive set in
 * state enum
 *
 * @param state_delta distance state (last error, integrated error..)
 * @param state_theta angular state (last error, integrated error..)
 */
void update_diff(pid_state_diff * state_delta, pid_state_diff * state_theta);

/**
 * @brief Converts pid output to motor directive.
 * @param sel motor selection
 * @param motor_ctrl converted from pid output
 */
int pid_to_motor(enum motor_sel sel,int motor_ctrl);

/**
 * @brief Computes PID from error
 *
 * @param state pid internal state
 * @param error Error in
 */
float pid_diff(pid_state * state, float error);

/**
 * @brief Set the directive variable in internal pid state
 *
 * @param state
 * @param directive
 */
void set_directive_diff(pid_state * state, float directive);