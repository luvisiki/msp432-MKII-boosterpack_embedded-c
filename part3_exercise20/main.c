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
    //configure RGB LED pwm
    config_blue_pwm();
    config_red_green_pwm();
    //configure ADC and joystic
    init_buttons_int();
    init_adc14();
    config_joystic();

    uint8_t duty_blue, duty_red, duty_green;
    uint16_t x = 0, y = 0;
    // init pwm
    pwm_blue(duty_blue);
    pwm_green(duty_green);
    pwm_red(duty_red);

    while (1)
    {
        /*
            USE JOYSTICK TO CONTROL RED/GREEN LED
            USE BUTTON TO CONTROL BLUE LED
            MIXED TOGETHER AND MAKE DIFFERENT COLORS LED
        */
        if (check_and_clear_bu_flag())
        {
            if (duty_blue == 100)
            {
                duty_blue = 100;
            }
            else
                duty_blue = duty_blue + 5;
            pwm_blue(duty_blue);
        }
        else if (check_and_clear_bb_flag())
        {
            if (duty_blue == 0)
            {
                duty_blue = 0;
            }
            else
                duty_blue = duty_blue - 5;
            pwm_blue(duty_blue);
        }
        read_joystick(&x, &y);
        // X asis: control green
        if (x < 6000)
        {
            if (duty_green == 0)
            {
                duty_green = 0;
            }
            else
                duty_green = duty_green - 5;
            pwm_green(duty_green);
        }
        else if (x > 12000)
        {
            if (duty_green == 100)
            {
                duty_green = 0;
            }
            else
                duty_green = duty_green + 5;
            pwm_green(duty_green);
        }
        // Y axis : control red
        if (y < 6000)
        {
            if (duty_red == 0)
            {
                duty_red = 0;
            }
            else
                duty_red = duty_red - 5;
            pwm_red(duty_red);
        }
        else if (y > 12000)
        {
            if (duty_red == 100)
            {
                duty_red = 0;
            }
            else
                duty_red = duty_red + 5;
            pwm_red(duty_red);
        }
        printf("red:%d ,green:%d ,blue:%d\n", duty_red, duty_green, duty_blue);
    }
}
