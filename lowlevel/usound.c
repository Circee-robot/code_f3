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

//void echo_setup(){
    //
    //_gpio_setup_pin(
            //R,
            //port,
            //pin,
            //mode,
            //pull_up_or_down,
            //otype
            //);
//}

void tim2_isr(){
    if (timer_get_flag(US_TRIGGER_TIM, TIM_SR_CC1IF)) // rising edge
	{
        //do something
        timer_clear_flag(US_TRIGGER_TIM, TIM_SR_CC1IF);
        timer_get_flag(US_TRIGGER_TIM, TIM_SR_CC1IF);

        gpio_set(US_TRIGGER_PORT,US_TRIGGER_PIN);
	}
    if (timer_get_flag(US_TRIGGER_TIM, TIM_SR_CC2IF)) // falling edge
	{
        //do something
        timer_clear_flag(US_TRIGGER_TIM, TIM_SR_CC2IF);
        timer_get_flag(US_TRIGGER_TIM, TIM_SR_CC2IF);

        gpio_clear(US_TRIGGER_PORT,US_TRIGGER_PIN);
	}
}
