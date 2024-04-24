#include "usound.h"

void trigger_setup(){
	_timer_setup(US_TRIGGER_TIM_RCC, US_TRIGGER_TIM, US_TRIGGER_PRESCALER_TIM, US_TRIGGER_PERIOD_TIM);

    nvic_enable_irq(US_TRIGGER_NVIC);

	_timer_setup_output_c(US_TRIGGER_TIM, TIM_OC1, TIM_OCM_FROZEN, US_TRIGGER_RISE_VALUE);
    timer_enable_irq(US_TRIGGER_TIM,TIM_DIER_CC1IE);

    _timer_setup_output_c(US_TRIGGER_TIM, TIM_OC2, TIM_OCM_FROZEN, US_TRIGGER_FALL_VALUE);
    timer_enable_irq(US_TRIGGER_TIM,TIM_DIER_CC2IE);

	_gpio_setup_pin(US_TRIGGER_GPIO_RCC, US_TRIGGER_PORT, US_TRIGGER_PIN, GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_OTYPE_PP);
	gpio_clear(US_TRIGGER_PORT,US_TRIGGER_PIN);

	/* start timer */
	_timer_start(US_TRIGGER_TIM);
}

void echo_setup(){
	/* Setup timer*/
	_timer_setup(US_ECHO_TIM_RCC,US_ECHO_TIM,US_ECHO_PRESCALER_TIM,US_ECHO_PERIOD_TIM);

	/*timer input capture*/
	timer_ic_set_input(US_ECHO_TIM, TIM_IC1, TIM_IC_IN_TI1);
	timer_direction_up(US_ECHO_TIM);
    timer_set_oc_polarity_low(US_ECHO_TIM, TIM_OC1);
    timer_set_oc_polarity_low(US_ECHO_TIM, TIM_OC1N);

    nvic_enable_irq(NVIC_TIM1_UP_TIM16_IRQ);
    timer_enable_irq(US_ECHO_TIM,TIM_DIER_CC1IE);

    /*Setup GPIO capture*/
    _gpio_setup_pin_af(US_ECHO_GPIO_RCC,US_ECHO_PORT,US_ECHO_PIN,US_ECHO_GPIO_AF,GPIO_PUPD_NONE,GPIO_OTYPE_PP);

    timer_ic_enable(US_ECHO_TIM, TIM_IC1);
}

// void tim2_isr(){
//     if (timer_get_flag(US_TRIGGER_TIM, TIM_SR_CC1IF)) // rising edge
// 	{
//         //do something
//         timer_clear_flag(US_TRIGGER_TIM, TIM_SR_CC1IF);
//         timer_get_flag(US_TRIGGER_TIM, TIM_SR_CC1IF);

//         gpio_set(US_TRIGGER_PORT,US_TRIGGER_PIN);
// 	}
//     if (timer_get_flag(US_TRIGGER_TIM, TIM_SR_CC2IF)) // falling edge
// 	{
//         //do something
//         timer_clear_flag(US_TRIGGER_TIM, TIM_SR_CC2IF);
//         timer_get_flag(US_TRIGGER_TIM, TIM_SR_CC2IF);

//         gpio_clear(US_TRIGGER_PORT,US_TRIGGER_PIN);
// 	}
// }


volatile bool measurement_started = false;
volatile int measurement_us = 0;

void tim1_up_tim16_isr(){
    int b = 8;
    if (!measurement_started)
    {
        if (timer_get_flag(US_ECHO_TIM, TIM_SR_CC1IF))
	    {
            timer_clear_flag(US_ECHO_TIM, TIM_SR_CC1IF);

            timer_disable_counter(US_ECHO_TIM);
            timer_set_counter(US_ECHO_TIM, 0);
            measurement_us = timer_get_counter(US_ECHO_TIM);
            timer_enable_counter(US_ECHO_TIM);
            measurement_started = true;
        }
        else
        {
            printf("Problem, interrupt but no flag raised");
        }
   }
   else
   {
    if (timer_get_flag(US_ECHO_TIM, TIM_SR_CC1IF))
	    {
        timer_clear_flag(US_ECHO_TIM, TIM_SR_CC1IF);
        measurement_us = timer_get_counter(US_ECHO_TIM) - measurement_us;
        measurement_started = false;
        }
        else
        {
            printf("Problem, interrupt but no flag raised");
        }
   }

    // if (timer_get_flag(US_ECHO_TIM, TIM_SR_CC1OF))
	// {
    //     timer_clear_flag(US_ECHO_TIM, TIM_SR_CC1OF);
    //     int b = 100;
    // }
}
