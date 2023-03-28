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
uint16_t read_temp(void);
float convert_to_volts(uint16_t reading);
float convert_to_Celsius(float volts);
void all_values_temp(uint16_t* ADC_value, float* voltage, float* Celsius);
void config_joystic(void);
void config_accel(void);
void read_joystick(uint16_t *x,uint16_t *y);
void read_accel(uint16_t *x, uint16_t *y, uint16_t *z);

extern volatile long temp;

#endif //MSP432_MKII_BOOSTERPACK_EMBEDDED_C_ANALOG_H
