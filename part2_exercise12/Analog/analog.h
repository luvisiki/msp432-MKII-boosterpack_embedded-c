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
float convert_to_volts(uint16_t reading);
float convert_to_Celsius(float volts);
void all_values_temp(uint16_t* ADC_value, float* voltage, float* Celsius);


extern volatile long temp;

#endif //MSP432_MKII_BOOSTERPACK_EMBEDDED_C_ANALOG_H
