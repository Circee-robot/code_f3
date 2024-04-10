/**
 * @file
 *
 * This file is part of cdfr2020BaseRoulanteRework
 *
 * @brief This implements the functions to test the project
 *
 * @date  01/2024
 *
 * Licence :
 *
 * @author NPXav Benano Kit
*/
#include "test.h"

void test_motor(){
    motor_setup();

    // timer_set_oc_value(MOTOR_TIM, MOTOR_A_OC_ID, 10000);
    // timer_set_oc_value(MOTOR_TIM, MOTOR_B_OC_ID, 10000);

    while(1){
    motor_set(MOTOR_A,100,FORWARD);
    delay_ms(40);
    motor_set(MOTOR_A,128,BACKWARD);
    delay_ms(40);
    motor_set(MOTOR_A,-1,STOP);
    delay_ms(40);
    motor_set(MOTOR_A,-1,FREE);
    delay_ms(40);

    motor_set(MOTOR_B,100,FORWARD);
    delay_ms(40);
    motor_set(MOTOR_B,128,BACKWARD);
    delay_ms(40);
    motor_set(MOTOR_B,-1,STOP);
    delay_ms(40);
    motor_set(MOTOR_B,-1,FREE);
    delay_ms(40);
    }
}
