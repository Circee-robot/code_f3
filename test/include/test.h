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
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "clock.h"
#include "motor.h"
#include "encoder.h"
#include "uart.h"
#include "timer_int.h"
#include "canmsgs.h"
#include "usound.h"

void test_us_trigger();
void test_motor();
void test_send_comm_usart();
void test_interrupt_timer();
void blink_led();
void test_can_transmit();
