/*
 * buttons.h
 *
 *  Created on: 2023年3月1日
 *      Author: luvisiki
 */

#ifndef BUTTONS_BUTTONS_H_
#define BUTTONS_BUTTONS_H_

#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>

//static uint8_t button_bottom_flag;  //global valueable.exercise4: change into static
//static uint8_t button_upper_flag;
//static uint8_t button_joystick_flag;
#define B_UP 0
#define B_BU 1
#define B_JS 2

void init_buttons (void);
uint8_t read_button_bottom (void);
uint8_t read_upper_bottom (void);

uint8_t button_bottom_fsm(void);
void init_buttons_int(void);
uint8_t check_and_clear_bb_flag (void); //button_bottom
uint8_t check_and_clear_bu_flag (void); //button_upper
uint8_t check_and_clear_bj_flag (void); //button_joystick
uint8_t check_and_clear_any_button_flag(uint8_t button); // check all

#endif /* BUTTONS_BUTTONS_H_ */



