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
    float pid_output_theta = pid(state_theta,error_theta);
    float pid_output_delta = pid(state_delta,error_delta);

    state_theta->last_pid_output = pid_output_theta;
    state_delta->last_pid_output = pid_output_delta;
    
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
    if(motor_ctrl > 150){
        motor_set(config.motor_sel,(uint8_t) (int)motor_ctrl, motor_dir);
        state->convergence_counter = 0;
    } else {
        if(state->convergence_counter > 30){
            motor_set(config.motor_sel,(uint8_t) (int)motor_ctrl, STOP);
            state->error_sum = 0;
        } else {
            state->convergence_counter++;
            motor_set(config.motor_sel,(uint8_t) (int)motor_ctrl, motor_dir);
        }
    }
    // motor_set(config.motor_sel,(uint8_t) (int)motor_ctrl, motor_dir);

    //fprintf(stderr,"Setting motor %d to %d\tdir=%d\n",config.motor_sel,(int)motor_ctrl*10000, motor_dir);
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

void reset_pid_diff(
    pid_state_diff * state
){
    state->last_error = 0;
    state->error_sum = 0;
    state->last_pid_output = 0;
    state->pos_tick = 0;
    state->convergence_counter = 0;
}
