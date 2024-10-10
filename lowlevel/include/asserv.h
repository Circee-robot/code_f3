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
 * @author NPXav Benano Kit Moi
 */

#pragma once
#include "clock.h"
#include "motor.h"
#include "encoder.h"

/**
 * Motor specific config structure for the PID
 */
typedef struct _config {
    enum motor_sel sel;
    float Kp;
    float Ki;
    float Kd;
} pid_config;

/**
 * Values of both motors' PIDs
 */
define KP_A (0);
define KI_A (0);
define KD_A (0);
define KP_B (0);
define KI_B (0);
define KD_B (0);

/**
 * Contains motor specific PID loop state
 */
typedef struct _state {
    float directive_rot;
    int prev_count;
    float last_error;
    float error_sum;
} pid_state;

/**
 * Rotation conversion values
 */
define MEASURE_PERIOD_MS  (20);
define TPS_TO_DUTY_RATIO (255/2.1);

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
float pid(float_error error, pid_config config, pid_state * state);
/**
 * @brief This function pilots the sel (MOTOR_A or MOTOR_B) with a value between -100(backward full speed) and +100 (forward full speed). The forward direction depends on the sign of MOTOR_X_INVER_DIR.
 *
 * @param sel The motor that will be piloted (eg MOTOR_A)
 * @param value value is between 0 and 255
 * @param state Motor config between STOP FREE FORWARD BACKWARD
 */
void get_directive(pid_state * state_A, pid_state * state_B);
