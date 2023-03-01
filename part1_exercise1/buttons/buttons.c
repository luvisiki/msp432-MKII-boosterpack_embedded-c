/*
 * buttons.c
 *
 *  Created on: 2023年3月1日
 *      Author: luvisiki
 */
#include "buttons.h"
#include <stdint.h>

void init_buttons (void)
{
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3,GPIO_PIN5); //bottom button
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5,GPIO_PIN1); //up button
}

uint8_t read_button_bottom (void)
{
    if(GPIO_getInputPinValue(GPIO_PORT_P3,GPIO_PIN5)==0)
    {
//        printf("bottom button push!");
        return 1;
    }
    return 0;
}

