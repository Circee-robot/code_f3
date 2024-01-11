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

    volatile int counterLeft;
    volatile int counterRight;

    //encoder testing
    while(1){
        encoder_update(ENCODER_A,&counterLeft);
        encoder_update(ENCODER_B,&counterRight);
        fprintf(stderr,"counterLeft=%d \t counterRight=%d \n",counterLeft,counterRight);
        delay_ms(100);
    }
}
