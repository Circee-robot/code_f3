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

    motor_set(MOTOR_A,70,FORWARD);
    motor_set(MOTOR_B,45,FORWARD);
    delay_ms(5000);
    motor_set(MOTOR_A,70,BACKWARD);
    motor_set(MOTOR_B,45,BACKWARD);
}
