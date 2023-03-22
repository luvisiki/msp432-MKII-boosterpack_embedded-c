//
// Created by Luvisiki Liu on 2023/3/15.
//

#ifndef MSP432_MKII_BOOSTERPACK_EMBEDDED_C_ANALOG_H
#define MSP432_MKII_BOOSTERPACK_EMBEDDED_C_ANALOG_H

#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>

void init_adc14(void);
void config_temp(void);
void read_temp(void);

#endif //MSP432_MKII_BOOSTERPACK_EMBEDDED_C_ANALOG_H
