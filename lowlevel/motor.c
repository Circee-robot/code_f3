#include "motor.h"

void motor_setup(){
    /* setup motor timer with a period of 20 ms 50Hz. One timer pilots
    both motors, using different channels of the output compare*/
    _timer_setup(MOTOR_TIM_RCC, MOTOR_TIM, PWM_PRESCALE, PWM_PERIOD);
    timer_enable_break_main_output(MOTOR_TIM);

    /* setup EN motor A (the PWM pin)*/
    _gpio_setup_pin_af(MOTOR_A_GPIO_RCC_EN, MOTOR_A_PORT_EN, MOTOR_A_PIN_EN, MOTOR_A_AF,GPIO_PUPD_NONE,GPIO_OTYPE_PP);
    _timer_setup_output_c(MOTOR_TIM, MOTOR_A_OC_ID, MOTOR_A_OC_MODE, 0);

    /* setup DIR motor A*/
    _gpio_setup_pin(MOTOR_A_GPIO_RCC_DIR,MOTOR_A_PORT_DIR,MOTOR_A_PIN_DIR,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_OTYPE_PP);
    /* setting motor A to free-running stop (EN=0) */
    timer_set_oc_value(MOTOR_TIM, MOTOR_B_OC_ID, 0);
    gpio_clear(MOTOR_A_PORT_DIR,MOTOR_A_PIN_DIR);

    // /* setup EN motor B (the PWM pin)*/
    _gpio_setup_pin_af(MOTOR_B_GPIO_RCC_EN, MOTOR_B_PORT_EN, MOTOR_B_PIN_EN, MOTOR_B_AF,GPIO_PUPD_NONE,GPIO_OTYPE_PP);
    _timer_setup_output_c(MOTOR_TIM, MOTOR_B_OC_ID, MOTOR_B_OC_MODE, 0);

    /* setup DIR motor B*/
    _gpio_setup_pin(MOTOR_B_GPIO_RCC_DIR,MOTOR_B_PORT_DIR,MOTOR_B_PIN_DIR,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_OTYPE_PP);
    /* setting motor B to free-running stop (EN=0) */
    timer_set_oc_value(MOTOR_TIM, MOTOR_B_OC_ID, 0);
    gpio_clear(MOTOR_B_PORT_DIR,MOTOR_B_PIN_DIR);

    /* setup sleep (EEP) pin */
    _gpio_setup_pin(MOTOR_GPIO_RCC_EEP,MOTOR_PORT_EEP,MOTOR_PIN_EEP,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_OTYPE_PP);
    gpio_set(MOTOR_PORT_EEP,MOTOR_PIN_EEP);

    /* start timer */
    _timer_start(MOTOR_TIM);
}

void motor_sleep(){
    gpio_clear(MOTOR_PORT_EEP,MOTOR_PIN_EEP);
}

void motor_set(enum motor_sel sel, uint8_t value, enum motor_state state){

    int speed;
    gpio_set(MOTOR_PORT_EEP,MOTOR_PIN_EEP);
    if(sel == MOTOR_B){
        /* control for motor B */
        switch(state){
            case STOP:
                /* fast motor stop DIR=X EN=0 */
                timer_set_oc_value(MOTOR_TIM, MOTOR_B_OC_ID, PWM_PERIOD + 1);
                break;
            case FORWARD:
                /* direction 1: EN=PWM DIR=1 */
                if(MOTOR_B_INVERT_DIR == 0){
                    gpio_clear(MOTOR_B_PORT_DIR,MOTOR_B_PIN_DIR);
                } else {
                    gpio_set(MOTOR_B_PORT_DIR,MOTOR_B_PIN_DIR);
                }
                speed = value * PWM_PERIOD/255.;
                timer_set_oc_value(MOTOR_TIM, MOTOR_B_OC_ID, speed);
                break;
            case BACKWARD:
                /* direction 2: EN=PWM DIR=0 */
                if(MOTOR_B_INVERT_DIR == 0){
                    gpio_set(MOTOR_B_PORT_DIR,MOTOR_B_PIN_DIR);
                } else {
                    gpio_clear(MOTOR_B_PORT_DIR,MOTOR_B_PIN_DIR);
                }
                speed = value * PWM_PERIOD/255.;
                timer_set_oc_value(MOTOR_TIM, MOTOR_B_OC_ID, speed);
                break;
        }
    } else {
        /* control for motor A */
        switch(state){
            case STOP:
                /* fast motor stop DIR=X EN=0 */
                timer_set_oc_value(MOTOR_TIM, MOTOR_A_OC_ID, PWM_PERIOD + 1);
                break;
            case FORWARD:
                /* direction 1: EN=PWM DIR=1 */
                if(MOTOR_A_INVERT_DIR == 0){
                    gpio_clear(MOTOR_A_PORT_DIR,MOTOR_A_PIN_DIR);
                } else {
                    gpio_set(MOTOR_A_PORT_DIR,MOTOR_A_PIN_DIR);
                }
                speed = value * PWM_PERIOD/255.;
                timer_set_oc_value(MOTOR_TIM, MOTOR_A_OC_ID, speed);
                break;
            case BACKWARD:
                /* direction 2: EN=PWM DIR=0 */
                if(MOTOR_A_INVERT_DIR == 0){
                    gpio_set(MOTOR_A_PORT_DIR,MOTOR_A_PIN_DIR);
                } else {
                    gpio_clear(MOTOR_A_PORT_DIR,MOTOR_A_PIN_DIR);
                }
                speed = value * PWM_PERIOD/255.;
                timer_set_oc_value(MOTOR_TIM, MOTOR_A_OC_ID, speed);
                break;
        }
    }
}
