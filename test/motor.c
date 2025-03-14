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

    while(1){
        motor_set(MOTOR_A,30,BACKWARD);
        motor_set(MOTOR_B,30,BACKWARD);
        // motor_set(MOTOR_A,-1,STOP);
        // delay_ms(4000);
        delay_ms(1000);
        // gpio_clear(MOTOR_B_PORT_DIR,MOTOR_B_PIN_DIR);
        // delay_ms(1000);
        // motor_set(MOTOR_A,128,BACKWARD);
        // delay_ms(4000);
        // motor_set(MOTOR_A,100,FORWARD);
        // delay_ms(4000);
        // delay_ms(40);
        // motor_set(MOTOR_A,-1,STOP);
        // delay_ms(40);
        // motor_set(MOTOR_A,-1,FREE);
        // delay_ms(40);

        motor_set(MOTOR_A,255,FORWARD);
        motor_set(MOTOR_B,255,FORWARD);
        delay_ms(1000);
        // motor_set(MOTOR_B,128,BACKWARD);
        // delay_ms(40);
        // motor_set(MOTOR_B,-1,STOP);
        // delay_ms(40);
        // motor_set(MOTOR_B,-1,FREE);
        // delay_ms(40);
    }
}
