/*
 * buttons.c
 *
 *  Created on: 2023年3月1日
 *      Author: luvisiki
 */
#include "buttons.h"
#include <stdint.h>

static uint8_t button_bottom_flag = 0;
void init_buttons(void)
{
    P5->SEL0 &= ~BIT1;
    P5->SEL1 &= ~BIT1;
    P5->DIR &= ~BIT1; // set GPIO
//    P5->REN |= BIT1;  // set Register,Don't enable pullup resistor, there is a resistor in the PCB.
//    P5->OUT |= BIT1;  // pull up set

    P3->SEL0 &= ~BIT5;
    P3->SEL1 &= ~BIT5;
    P3->DIR &= ~BIT5;
//    P3->REN |= BIT5;
//    P3->OUT |= BIT5;
}

void init_buttons_int(void)
{
    /*
     * configure the bottom button and enable its interrupt.
     */
    init_buttons();

    P5->IE |= BIT1;      //enable interrupt
    P5->IFG &= ~BIT1;    // clear first

    P3->IE |= BIT5;         //enable interrupt
    P3->IFG &= ~BIT5;       // clear first
    NVIC->ISER[1] |= 0x01 << (PORT3_IRQn & 31);
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

uint8_t check_and_clear_bb_flag(void)
{
    uint8_t copy;
    uint32_t states;
    states = __get_interrupt_state();
    __disable_interrupt();
    copy = button_bottom_flag;
    button_bottom_flag=0;
    __set_interrupt_state(states);
    return copy;
}

extern void PORT3_IRQHandler(void)
{

//    if (P3->IFG & BIT5) // check the pin raised the interrupt
//    {
//        P3->IFG &= ~BIT5;
//        button_bottom_flag = 1;
//    }
    uint8_t states;
    //Reading PxIV automatically clear the corresponding flag in PxIFG.
    states = P3->IV;
    if (states == DIO_PORT_IV__IFG5)    // There are constants to use instead of numerical values. DIO_PORT_IV__IFGx
    {
        states = 0;
        button_bottom_flag = 1;
    }
}
