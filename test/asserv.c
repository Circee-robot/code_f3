#include "asserv.h"

int test_asserv(){
    encoder_setup();
    uart_setup();
    motor_setup();

    pid_config config_A = {
        .motor_sel = MOTOR_A,
        .encoder_sel = ENCODER_A,
        .Kp = KP_A,
        .Ki = KI_A,
        .Kd = KD_A
    };
    // pid_config config_B = {
    //     .motor_sel = MOTOR_B,
    //     .encoder_sel = ENCODER_B,
    //     .Kp = KP_B,
    //     .Ki = KI_B,
    //     .Kd = KD_B
    // };
    pid_state state_A = EMPTY_STATE;
    // pid_state state_B = EMPTY_STATE;

    set_directive(&state_A, 100);

    while(true){
        update_motor(config_A, &state_A);

        delay_ms(MEASURE_PERIOD_MS);
    }
}
