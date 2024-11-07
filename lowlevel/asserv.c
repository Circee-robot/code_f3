// #include "asserv.h"

// void update_motor(pid_config config, pid_state * state){
//     // Choosing encoder depending on motor
//     if (dire.sel == MOTOR_A){
//         counter = encoder_update(ENCODER_A,state->prev_count);
//     } else {
//         counter = encoder_update(ENCODER_B,state->prev_count);
//     }
//     // Calculating PID
//     float measured_rot = counter / MEASURE_PERIOD_MS;
//     float error = state->directive_rot - measured_rot;
//     float motor_ctrl = pid(error,config,state); // TODO switch dire
//     // Direction switch
//     if (motor_ctrl >= 0) {
//         enum motor_state dir = FORWARD;
//     } else {
//         motor_ctrl = motor_ctrl * (-1);
//         enum motor_state dir = BACKWARD;
//     }
//     //
//     uint8_t motor_ctrl_duty = motor_ctrl * TPS_TO_DUTY_RATIO;
//     motor_set(config.sel, motor_ctrl_duty, dir);
// }

// float pid(float error, pid_config config, pid_state * state){

//     float P,I,D;

//     state->error_sum += error;

//     P = error * config.Kp;a
//     I = state->error_sum * config.Ki;
//     D = (error - state->last_error) * config.Kd;

//     state->last_error = error;

//     return (P+I+D);
// }


// void get_directive(pid_state * state_A, pid_state * state_B){
//     state_A->directive_rot = 2;
//     state_B->directive_rot = 2;
// }
