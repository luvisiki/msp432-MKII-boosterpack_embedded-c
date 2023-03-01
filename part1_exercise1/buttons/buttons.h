/*
 * buttons.h
 *
 *  Created on: 2023年3月1日
 *      Author: luvisiki
 */

#ifndef BUTTONS_BUTTONS_H_
#define BUTTONS_BUTTONS_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <stdint.h>

void init_buttons (void);
uint8_t read_button_bottom (void);


#endif /* BUTTONS_BUTTONS_H_ */



