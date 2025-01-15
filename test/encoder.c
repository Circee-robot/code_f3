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

void test_encoder(){
    encoder_setup();
    uart_setup();
    motor_setup();

    // motor_sleep();
    motor_set(MOTOR_A,50,FORWARD);
    motor_set(MOTOR_B,70,FORWARD);


    volatile int counterLeft = 0;
    volatile int counterRight = 0;

    int dist_b;

    //encoder testing
    while(1){

        // encoder_update(ENCODER_A,&counterLeft);
        dist_b = encoder_update(ENCODER_B,&counterRight);
        fprintf(stderr,"counterLeft=%d \t speedleft=%d \t counterRight=%d \n",counterLeft,dist_b,counterRight);
        delay_ms(500);
    }
}
