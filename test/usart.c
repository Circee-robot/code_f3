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

void test_send_comm_usart(){
  uart_setup();
  uint16_t myInt = 20;

  while (1)
  {
    fprintf(stderr,"err %d \n",myInt);
    // fprintf(stdout,"out %d \n",myInt);
    // usart_send_blocking(DEBUG_USART,'a');
    myInt ++;
    delay_ms(500);
    // fprintf(stderr,"sending a string : hello\n");
    // fprintf(stdout,"hello");
  }

}
