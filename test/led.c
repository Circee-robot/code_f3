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

void blink_led(){     //led is on PB3
    _gpio_setup_pin(LED_GPIO_RCC,LED_GPIO_PORT,LED_GPIO_PIN,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_OTYPE_PP);
    while(1){
        gpio_toggle(LED_GPIO_PORT,LED_GPIO_PIN);
        delay_ms(100);
    }
}
