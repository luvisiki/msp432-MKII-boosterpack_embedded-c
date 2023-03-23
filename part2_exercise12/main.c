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
    config_temp();
    uint16_t ADC_value;
    float volts;
    float temperature;
    while (1)
    {
        //        read_temp();
        //        uint16_t value = temp;
        //        float volts = convert_to_volts(value);
        //        float temperature = convert_to_Celsius(volts);
        //        printf("Celsius: %.5f \n",temperature);

        all_values_temp(&ADC_value,&volts,&temperature);
        printf("ADC reading: %d,Voltage: %.5f,Temperature: %.5f\n", ADC_value, volts, temperature);
    }
}
