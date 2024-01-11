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

void test_can_transmit(){
    int len = 2;
    uint8_t* pdata = calloc(len,sizeof(*pdata));
    pdata[0] = 0xbe;
    pdata[1] = 0xef;
    uint32_t id = 0b00000111111; //0x3f

    can_setup();
    int status = 96;

    // _gpio_setup_pin(LED_GPIO_RCC,LED_GPIO_PORT,LED_GPIO_PIN,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_OTYPE_PP);

    do{
        pdata[0] = 0xf3;
        pdata[1] = 0xaa;
        status = can_transmit(CAN1, id, false, false,len,pdata);
        fprintf(stderr,"transmission status: %d\n",status);
        delay_ms(100);

        pdata[0] = 0xf3;
        pdata[1] = 0xbb;
        status = can_transmit(CAN1, id, false, false,len,pdata);
        fprintf(stderr,"transmission status: %d\n",status);
        delay_ms(100);
    }while(!status);
}
