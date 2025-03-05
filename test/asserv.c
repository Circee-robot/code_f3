#include "asserv.h"

#define ARRAY_SIZE (1000)

volatile int measure_array[ARRAY_SIZE];

void test_asserv(){
    encoder_setup();
    uart_setup();
    motor_setup();

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
    pid_state state_A = EMPTY_STATE;
    pid_state state_B = EMPTY_STATE;

    set_directive(&state_A, 10000);
    set_directive(&state_B, 10000);
    int cnt = 0;

    while(true){
        update_motor(config_A, &state_A);
        update_motor(config_B, &state_B);
        //fprintf(stderr,
        //"Motor update: directive is %d, error was %d, last pid output was %d, position is %d\n",
        //(int)state_A.directive_tick,
        //(int)state_A.last_error,
        //(int)state_A.last_pid_output,
        //state_A.pos_tick);

        measure_array[cnt] = state_A.error_sum;

        if (cnt ==ARRAY_SIZE){
            fprintf(stderr,"\nnew array\n");
            for (int i=0; i<ARRAY_SIZE;i++){
                fprintf(stderr,", %d",measure_array[i]);
            }
            cnt = 0;
        }
        else{
            cnt ++;
        }

        delay_ms(MEASURE_PERIOD_MS);
    }
}
