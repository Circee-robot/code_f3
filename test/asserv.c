
int main(){
    pid_config config_A = {
        .sel = MOTOR_A,
        .Kp = KP_A,
        .Ki = KI_A,
        .Kd = KD_A
    };
    pid_config config_B = {
        .sel = MOTOR_B,
        .Kp = KP_B,
        .Ki = KI_B,
        .Kd = KD_B
    };
    pid_state state_A = { 0, 0, 0, 0 };
    pid_state state_B = { 0, 0, 0, 0 };

    while(true){

        get_directive(&state_A, &state_B);
        update_motor(config_A, &state_A);
        update_motor(config_B, &state_B);

        delay_ms();
    }
}
