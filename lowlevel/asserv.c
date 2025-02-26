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
    // float motor_ctrl = (pid_output - state->last_pid_output);
    float motor_ctrl = pid_output;

    state->last_pid_output = pid_output;
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


    // Stop condition TODO better conditions
    if(motor_ctrl > 100){
        motor_set(config.motor_sel,(uint8_t) (int)motor_ctrl, motor_dir);
        state->convergence_counter = 0;
    } else {
        if(state->convergence_counter > 30){
            motor_set(config.motor_sel,(uint8_t) (int)motor_ctrl, STOP);
        } else {
            state->convergence_counter++;
            motor_set(config.motor_sel,(uint8_t) (int)motor_ctrl, motor_dir);
        }
    }

    // fprintf(stderr,"Setting motor %d to %d\tdir=%d\n",config.motor_sel,(int)motor_ctrl*10000, motor_dir);
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
