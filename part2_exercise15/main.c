#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include "game.h"
#include "buttons/buttons.h"
#include "LED/led.h"
#include "Analog/analog.h"
// where you write your application.

/**
 * main.c
 */

void main(void)
{

    init_adc14();
    // config_temp();
    config_joystic();

    // uint16_t ADC_value;
    // float volts;
    // float temperature;

    uint16_t x;
    uint16_t y;
    while (1)
    {
        //        read_temp();
        //        uint16_t value = temp;
        //        float volts = convert_to_volts(value);
        //        float temperature = convert_to_Celsius(volts);
        //        printf("Celsius: %.5f \n",temperature);
        // all_values_temp(&ADC_value,&volts,&temperature);
        // printf("ADC reading: %d,Voltage: %.5f,Temperature: %.5f\n", ADC_value, volts, temperature);
        read_joystick(&x,&y);
        printf("x: %d, y: %d \n",x,y);      //value between 0~16370+
    }
    
}
