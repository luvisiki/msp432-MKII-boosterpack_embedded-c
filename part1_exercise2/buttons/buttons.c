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
//    P5->REN |= BIT1;  // set Register,Don't enable pullup resistor, there is a resistor in the PCB.
//    P5->OUT |= BIT1;  // pull up set , once you use fsm there is no necessary to set pull up

    P3->SEL0 &= ~BIT5;
    P3->SEL1 &= ~BIT5;
    P3->DIR &= ~BIT5;
//    P3->REN |= BIT5;
//    P3->OUT |= BIT5;
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

uint8_t button_bottom_fsm(void)
{
    static uint8_t FSM_state = 0; //
    switch (FSM_state)
    {
    case 0: //first pressed
        if (read_button_bottom() == 1)
        {
            FSM_state = 1;
            return 1;
        }
        else
            return 0;
    case 1: //still pressed
        if (read_button_bottom() == 1)
        {
            return 0;
        }
        else
        {
            FSM_state = 0;
            return 0;
        }

    }
    return 0;
}
