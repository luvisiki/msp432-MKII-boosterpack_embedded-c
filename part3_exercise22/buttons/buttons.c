/*
 * buttons.c
 *
 *  Created on: 2023年3月1日
 *      Author: luvisiki
 */
#include "buttons.h"
#include <stdint.h>

static uint8_t button_bottom_flag = 0;
static uint8_t button_joystick_flag = 0;
static uint8_t button_upper_flag = 0;

void init_buttons(void) {
    // configure all the GPIO pins

    P5->SEL0 &= ~BIT1; // upper button
    P5->SEL1 &= ~BIT1;
    P5->DIR &= ~BIT1; // set GPIO
    //    P5->REN |= BIT1;  // set Register,Don't enable pullup resistor, there is a resistor in the PCB.
    //    P5->OUT |= BIT1;  // pull up set

    P3->SEL0 &= ~BIT5; // Bottom button
    P3->SEL1 &= ~BIT5;
    P3->DIR &= ~BIT5;

    P4->SEL0 &= ~BIT1; // joystick select
    P4->SEL1 &= ~BIT1;
    P4->DIR &= ~BIT1;
}

void init_buttons_int(void) {
    /*
     * configure the bottom button and enable its interrupt.
     */
    init_buttons();

    P5->IES |= BIT1;
    P3->IES |= BIT5;
    P4->IES |= BIT1;

    P5->IFG &= ~BIT1; // clear first
    P3->IFG &= ~BIT5;
    P4->IFG &= ~BIT1;

    P5->IE |= BIT1;   // enable interrupt
    P3->IE |= BIT5;
    P4->IE |= BIT1;

    NVIC_EnableIRQ(PORT3_IRQn);//
    NVIC_EnableIRQ(PORT4_IRQn);//
    NVIC_EnableIRQ(PORT5_IRQn);//
//    NVIC->ISER[1] |= 0x01 << (PORT3_IRQn & 31);
//    NVIC->ISER[1] |= 0x01 << (PORT4_IRQn & 31);
//    NVIC->ISER[1] |= 0x01 << (PORT5_IRQn & 31);
}

uint8_t read_button_bottom(void) {
    uint8_t value1;
    value1 = P3IN & BIT5;
    if (value1 > 0) {
        return 0;
    } else
        return 1;
}

uint8_t read_upper_bottom(void) {
    uint8_t value1;
    value1 = P5IN & BIT1;
    if (value1 > 0) {
        return 0;
    } else
        return 1;
}

uint8_t button_bottom_fsm(void) {
    static uint8_t FSM_state = 0; //
    switch (FSM_state) {
        case 0: // first pressed
            if (read_button_bottom() == 1) {
                FSM_state = 1;
                return 1;
            } else
                return 0;
        case 1: // still pressed
            if (read_button_bottom() == 1) {
                return 0;
            } else {
                FSM_state = 0;
                return 0;
            }
    }
    return 0;
}

uint8_t check_and_clear_bb_flag(void) // button_bottom
{
//    uint8_t value;
//    if (button_bottom_flag == 1) {
//        value = button_bottom_flag;
//        button_bottom_flag = 0;
//        return value;
//    } else
//        return 0;
    uint8_t copy;
    uint32_t states;
    states = __get_interrupt_state();
    __disable_interrupt();
    copy = button_bottom_flag;
    button_bottom_flag = 0;
//    __enable_interrupt(); not use easy enable interrupt,using restore
    __set_interrupt_state(states);
    return copy;
}

uint8_t check_and_clear_bj_flag(void) // button_joystick
{
    uint8_t copy;
    uint32_t states;
    states = __get_interrupt_state();
    __disable_interrupt();
    copy = button_joystick_flag;
    button_joystick_flag = 0;
//    __enable_interrupt(); not use easy enable interrupt,using restore
    __set_interrupt_state(states);
    return copy;
}

uint8_t check_and_clear_bu_flag(void) // button_upper
{
    uint8_t copy;
    uint32_t states;
    states = __get_interrupt_state();
    __disable_interrupt();
    copy = button_upper_flag;
    button_upper_flag = 0;
//    __enable_interrupt(); not use easy enable interrupt,using restore
    __set_interrupt_state(states);
    return copy;
}

extern void PORT3_IRQHandler(void) {
    uint8_t states;
    // Reading PxIV automatically clear the corresponding flag in PxIFG.
    states = P3->IV;
    if (states == DIO_PORT_IV__IFG5) // There are constants to use instead of numerical values. DIO_PORT_IV__IFGx
    {
        states = 0;
        button_bottom_flag = 1;
    }
}

extern void PORT4_IRQHandler(void) {

    switch (P4->IV) {
        case DIO_PORT_IV__IFG1:
            button_joystick_flag = 1;
            break;

        default:
            break;
    }
}

extern void PORT5_IRQHandler(void) {
    switch (P5->IV) {
        case DIO_PORT_IV__IFG1:
            button_upper_flag = 1;
            break;

        default:
            break;
    }
}
