#include "asserv.h"

void test_straight_line(){

    // Low level setup
    encoder_setup();
    uart_setup();
    motor_setup();

    // PID config from `asserv.h`
    pid_config config_A = {
        .motor_sel = MOTOR_A,
        .encoder_sel = ENCODER_A,
        .Kp = KP_A,
        .Ki = KI_A,
        .Kd = KD_A,
        .imax = IMAX
    };
    pid_config config_B = {
        .motor_sel = MOTOR_B,
        .encoder_sel = ENCODER_B,
        .Kp = KP_B,
        .Ki = KI_B,
        .Kd = KD_B,
        .imax = IMAX
    };

    // PID state & friends intialisation
    pid_state state_A = EMPTY_STATE;
    pid_state state_B = EMPTY_STATE;
    int segment_counter = 0;
    int segment_time = clock_get_systicks();
    set_directive(&state_A, 10000);
    set_directive(&state_B, 10000);

    while(true){
        // Every 8 seconds, reset pid state and add 10000 to directive
        if(clock_get_systicks() - segment_time < 8000){
            segment_time = clock_get_systicks();
            segment_counter++;
            set_directive(&state_A, 10000 * segment_counter);
            set_directive(&state_B, 10000 * segment_counter);
            reset_pid(&state_A);
            reset_pid(&state_B);
        }

        // PID loop
        update_motor(config_A, &state_A);
        update_motor(config_B, &state_B);
        delay_ms(MEASURE_PERIOD_MS);
    }
}
