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
 * @param config Motor specific config coefficients
 * @param state Motor specific state (last error, integrated error..)
 */
void update_diff(pid_state_diff * state_delta, pid_state_diff * state_theta);
/**
 * @brief Computes PID from error
 *
 * @param error Error in
 * @param value value is between 0 and 255
 * @param state Motor config between STOP FREE FORWARD BACKWARD
 */
float pid_diff(pid_state * state, float error);
/**
 * @brief This function pilots the motor_sel (MOTOR_A or MOTOR_B) with a value between -100(backward full speed) and +100 (forward full speed). The forward direction depends on the sign of MOTOR_X_INVER_DIR.
 *
 * @param state
 */
void set_directive_diff(pid_state * state, float directive);
/**
 * @brief This function resets a pid's state as if the motor was at position 0
 *
 * @param state
 */
void reset_pid(pid_state * state);
