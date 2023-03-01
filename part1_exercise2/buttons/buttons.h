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

void init_buttons (void);
uint8_t read_button_bottom (void);
uint8_t button_bottom_fsm(void);

#endif /* BUTTONS_BUTTONS_H_ */



