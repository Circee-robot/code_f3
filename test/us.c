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

void test_us_trigger(){
    trigger_setup();

    while (1);
}


void test_us_echo(){
    echo_setup();
    _gpio_setup_pin(LED_GPIO_RCC,LED_GPIO_PORT,LED_GPIO_PIN,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_OTYPE_PP);
    int counter_debut;
    int counter_fin;

    while (1){
        _timer_start(US_ECHO_TIM);
        counter_debut = timer_get_counter(US_ECHO_TIM);
        delay_ms(5);
        gpio_set(LED_GPIO_PORT,LED_GPIO_PIN);
        delay_ms(10);
        gpio_clear(LED_GPIO_PORT,LED_GPIO_PIN);
        delay_ms(5);
        counter_fin = timer_get_counter(US_ECHO_TIM);
        delay_ms(1000);
    }
}
