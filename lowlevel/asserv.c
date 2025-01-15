#include "asserv.h"

void update_motor(
    pid_config config,
    pid_state * state
){
    // Choosing encoder depending on motor
    state->pos_tick += encoder_update(config.encoder_sel,&(state->encoder_tick_prev));
    // Calculating PID
    float error = state->directive_tick - state->pos_tick;
    float pid_output = pid(config,state,error);
    float motor_ctrl = (pid_output - state->last_pid_output);
    state->last_pid_output = pid_output;
    // Direction switch
    enum motor_state motor_dir;
    if (motor_ctrl >= 0) {
        motor_dir = FORWARD;
    } else {
        motor_ctrl = motor_ctrl * (-1);
        motor_dir = BACKWARD;
    }
    motor_set(config.motor_sel,(uint8_t) motor_ctrl, motor_dir);
}

float pid(
    pid_config config,
    pid_state * state,
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


void set_directive(
    pid_state * state,
    float directive
){
    *state = EMPTY_STATE;
    state->directive_tick = directive;
}
