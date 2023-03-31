#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include "game.h"
#include "buttons/buttons.h"
#include "LED/led.h"
#include "Analog/analog.h"
#include "timer/timer.h"

// where you write your application.

/**
 * main.c
 */

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Stop WDT
    config_blue_pwm();
    init_buttons_int();
    uint8_t duty;
    pwm_blue(duty);
    while (1)
    {
        if (check_and_clear_bu_flag())
        {
            if (duty == 100)
            {
                duty = 100;
            }
            else
                duty = duty + 5;
            pwm_blue(duty);
        }
        else if (check_and_clear_bb_flag())
        {
            if (duty == 0)
            {
                duty = 0;
            }
            else
                duty = duty - 5;
            pwm_blue(duty);
        }
        printf("duty: %d\n", duty);
    }
}
