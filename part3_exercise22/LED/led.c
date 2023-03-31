//
// Created by Luvisiki Liu on 2023/3/15.
//

#include "led.h"
#include "timer/timer.h"
#include "game.h"
#include "Analog/analog.h"

static uint8_t R, G, B;

void init_rgb(void)
{

    // led in MARKII package has already pullup resistor.
    P2->DIR |= BIT6; // j4.39 red
    P2->DIR |= BIT4; // j4.38 green
    P5->DIR |= BIT6; // j4.37 blue

    // GPIO set
    P2->SEL0 &= ~BIT6;
    P2->SEL1 &= ~BIT6;
    P2->SEL0 &= ~BIT4;
    P2->SEL1 &= ~BIT4;
    P5->SEL0 &= ~BIT6;
    P5->SEL1 &= ~BIT6;

    // output low
    P2->OUT &= ~BIT6;
    P2->OUT &= ~BIT4;
    P5->OUT &= ~BIT6;
}

void led_set(uint8_t r, uint8_t g, uint8_t b)
{
    R = r;
    G = g;
    B = b;
    pwm_blue(B);
    pwm_red(R);
    pwm_green(G);
}

void led_on(color)
{
    // output from low into high
    switch (color)
    {
    case 0: // red
        led_set(10, 0, 0);
        break;
    case 1: // green
        led_set(0, 10, 0);
        break;

    case 2: // blue
        led_set(0, 0, 10);
        break;
    default:
        break;
    }
}

void led_off(void)
{
    P2->OUT &= ~BIT6;
    P2->OUT &= ~BIT4;
    P5->OUT &= ~BIT6;
}
