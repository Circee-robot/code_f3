#include "asserv_differential.h"

void update_diff(
    pid_state_diff * state_delta,
    pid_state_diff * state_theta,
    encoder_state * encoder_state
){
    // Choosing encoder depending on motor
    int encoder_A = encoder_update(ENCODER_A, &(encoder_state->prev_A));
    int encoder_B = encoder_update(ENCODER_B, &(encoder_state->prev_B));

    state_theta->pos_value += encoder_B - encoder_A; // c la faute a xavier
    state_delta->pos_value += (encoder_A + encoder_B) / 2;

    // Calculating PID
    float error_theta = state_theta->directive_value - state_theta->pos_value;
    float error_delta = state_delta->directive_value - state_delta->pos_value;
    float pid_output_theta = pid_diff(state_theta,error_theta);
    float pid_output_delta = pid_diff(state_delta,error_delta);

    state_theta->last_pid_output = pid_output_theta;
    state_delta->last_pid_output = pid_output_delta;

    float motor_ctrl_B =  pid_output_delta + pid_output_theta / 2;
    float motor_ctrl_A =  pid_output_delta - pid_output_theta / 2;

    pid_to_motor(MOTOR_B, motor_ctrl_B);
    pid_to_motor(MOTOR_A, motor_ctrl_A);
}

int pid_to_motor(enum motor_sel sel,int motor_ctrl){
    // Direction switch
    enum motor_state motor_dir;
    if (motor_ctrl >= 0) {
        motor_dir = FORWARD;
    } else {
        motor_ctrl = motor_ctrl * (-1);
        motor_dir = BACKWARD;
    }
    if (motor_ctrl>255){
        motor_ctrl = 255;
    }

    motor_set(sel,(uint8_t) (int)motor_ctrl, motor_dir);

    return 0;
}

float pid_diff(
    pid_state_diff * state,
    float error
){

    float P,I,D;

    state->error_sum += error;
    if (state->error_sum > config.imax)
    {
        state->error_sum = config.imax;
    }
    else if (state->error_sum < -config.imax)
    {
        state->error_sum = -config.imax;
    }

    P = error * config.Kp;
    I = state->error_sum * config.Ki;
    D = (error - state->last_error) * config.Kd;

    state->last_error = error;

    return (P+I+D);
}


void set_directive_diff(
    pid_state_diff * state,
    float directive
){
    *state = EMPTY_STATE;
    state->directive_tick = directive;
}