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
  uint16_t myInt = 20;
  fprintf(stderr,"sending a int: %d \n",myInt);
  //usart_send_blocking(COMM_USART,myInt);
  fprintf(stdout,"%d",myInt);
  // fprintf(stderr,"sending a string : hello\n");
  // fprintf(stdout,"hello");
}
