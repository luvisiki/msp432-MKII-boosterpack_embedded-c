//
// Created by Luvisiki Liu on 2023/3/15.
//

#ifndef MSP432_MKII_BOOSTERPACK_EMBEDDED_C_LED_H
#define MSP432_MKII_BOOSTERPACK_EMBEDDED_C_LED_H

#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>

void init_rgb(void);

void led_on(color);

void led_off(void);

#endif //MSP432_MKII_BOOSTERPACK_EMBEDDED_C_LED_H
