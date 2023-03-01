/*
 * buttons.c
 *
 *  Created on: 2023年3月1日
 *      Author: luvisiki
 */
#include "buttons.h"
#include <stdint.h>

void init_buttons(void)
{
    P5->SEL0 &= ~BIT1;
    P5->SEL1 &= ~BIT1;
    P5->DIR &= ~BIT1; // set GPIO
//    P5->REN |= BIT1;  // set Register
    P5->OUT |= BIT1;  // pull up set

    P3->SEL0 &= ~BIT5;
    P3->SEL1 &= ~BIT5;
    P3->DIR &= ~BIT5;
//    P3->REN |= BIT5;
    P3->OUT |= BIT5;
}

uint8_t read_button_bottom(void)
{
    uint8_t value1;
    value1 = P3IN & BIT5;
    if (value1 > 0)
    {
        return 0;
    }
    else
        return 1;
}

