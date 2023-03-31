/*
 * timer.c
 *
 *  Created on: 2023.3.30
 *      Author: luvisiki
 */

#include "msp.h"
#include "timer.h"
#include <stdint.h>

void config_blue_pwm(void)
{
    // configure blue LED DIo
    P5->DIR |= BIT6;
    P5->SEL0 |= BIT6;
    P5->SEL1 &= ~BIT6;

    TA2CTL = 0;
    TA2CCR0 = 7500;                      // 24MHz / 4 /800hz = 7500
    TA2CCR1 = 1875;                      // duty cycle for 25%: 7500/4 = 1875
    TA2CTL |= (TIMER_A_CTL_SSEL__SMCLK | // use SMCLK clock:24MHz
               TIMER_A_CTL_MC__UP |      // Up mode: Timer counts up to TAxCCR0
               TIMER_A_CTL_ID__4 |       // use divided 4
               TIMER_A_CTL_CLR);         // TimerA clear

    TA2CCTL1 |= TIMER_A_CCTLN_OUTMOD_7; // mode 7
}
void config_red_green_pwm(void)
{
    /*
        configure the red and green leds to be controlled by PWM
    */

    // RED LED
    P2->DIR |= BIT6;
    P2->SEL0 |= BIT6;
    P2->SEL1 &= ~BIT6;
    // GREEN LED
    P2->DIR |= BIT4;
    P2->SEL0 |= BIT4;
    P2->SEL1 &= ~BIT4;

    TA0CTL = 0;
    TA0CCR0 = 7500;
    TA0CCR1 = 1875;                     // GREEN LED CCR1
    TA0CCR3 = 1875;                     // RED LED CCR3
    TA0CTL = (TIMER_A_CTL_SSEL__SMCLK | // CLOCK
              TIMER_A_CTL_MC__UP |      // UP MODE
              TIMER_A_CTL_ID__4 |       // DIVIDE 4
              TIMER_A_CTL_CLR);         // CLEAR

    // GREED RED OUTPUT MODE :7
    TA0CCTL1 |= TIMER_A_CCTLN_OUTMOD_7;
    TA0CCTL3 |= TIMER_A_CCTLN_OUTMOD_7;
}

uint8_t pwm_blue(uint8_t duty)
{
    /*
        decription:
        function will receive the duty cycle for the blue led in percentage,
        in the range 0% to 100%
    */
    uint16_t count = ((uint32_t)duty * 7500) / 100;
    // duty below 5%:
    if (duty < 5)
    {
        TA2CCTL1 &= ~TIMER_A_CCTLN_OUT;
        TA2CCTL1 &= ~TIMER_A_CCTLN_OUTMOD_MASK; // mode change to 0
        TA2CTL |= TIMER_A_CTL_CLR;
        return 0;
    }
    // duty above 95%
    else if (duty > 95)
    {
        TA2CCTL1 &= ~TIMER_A_CCTLN_OUTMOD_MASK; // OUTMODE:0
        TA2CCTL1 |= TIMER_A_CCTLN_OUT;          // OUT:1
        TA2CTL |= TIMER_A_CTL_CLR;              // CLEAR
        return 0;
    }
    // duty out of (0,100)
    else if (duty < 0 || duty > 100)
    {
        TA2CCTL1 &= ~TIMER_A_CCTLN_OUT;         // SET OUT 0
        TA2CCTL1 &= ~TIMER_A_CCTLN_OUTMOD_MASK; // OUTPUT MODE : 0
        TA2CTL |= TIMER_A_CTL_CLR;
        return 1;
    }
    else if (5 < duty || duty < 95)
    {
        TA2CCR0 = 7500;
        TA2CCR1 = count;
        TA2CTL |= TIMER_A_CTL_CLR;
        TA2CCTL1 &= ~TIMER_A_CCTLN_OUTMOD_MASK;
        TA2CCTL1 |= TIMER_A_CCTLN_OUTMOD_7; // OUTPUT MODE:7
        return 0;
    }
}

uint8_t pwm_red(uint8_t duty)
{
    /*
        decription:
        function will receive the duty cycle for the blue led in percentage,
        in the range 0% to 100%
    */
    uint16_t count = ((uint32_t)duty * 7500) / 100;
    // duty below 5%:
    if (duty < 5)
    {
        TA0CCTL3 &= ~TIMER_A_CCTLN_OUT;
        TA0CCTL3 &= ~TIMER_A_CCTLN_OUTMOD_MASK; // mode change to 0
        TA0CTL |= TIMER_A_CTL_CLR;
        return 0;
    }
    // duty above 95%
    else if (duty > 95)
    {
        TA0CCTL3 &= ~TIMER_A_CCTLN_OUTMOD_MASK; // OUTMODE:0
        TA0CCTL3 |= TIMER_A_CCTLN_OUT;          // OUT:1
        TA0CTL |= TIMER_A_CTL_CLR;              // CLEAR
        return 0;
    }
    // duty out of (0,100)
    else if (duty < 0 || duty > 100)
    {
        TA0CCTL3 &= ~TIMER_A_CCTLN_OUT;         // SET OUT 0
        TA0CCTL3 &= ~TIMER_A_CCTLN_OUTMOD_MASK; // OUTPUT MODE : 0
        TA0CTL |= TIMER_A_CTL_CLR;
        return 1;
    }
    else if (5 < duty || duty < 95)
    {
        TA0CCR0 = 7500;
        TA0CCR3 = count;
        TA0CTL |= TIMER_A_CTL_CLR;
        TA0CCTL3 &= ~TIMER_A_CCTLN_OUTMOD_MASK;
        TA0CCTL3 |= TIMER_A_CCTLN_OUTMOD_7; // OUTPUT MODE:7
        return 0;
    }
}

uint8_t pwm_green(uint8_t duty)
{
    /*
        decription:
        function will receive the duty cycle for the blue led in percentage,
        in the range 0% to 100%
    */
    uint16_t count = ((uint32_t)duty * 7500) / 100;
    // duty below 5%:
    if (duty < 5)
    {
        TA0CCTL1 &= ~TIMER_A_CCTLN_OUT;
        TA0CCTL1 &= ~TIMER_A_CCTLN_OUTMOD_MASK; // mode change to 0
        TA0CTL |= TIMER_A_CTL_CLR;
        return 0;
    }
    // duty above 95%
    else if (duty > 95)
    {
        TA0CCTL1 &= ~TIMER_A_CCTLN_OUTMOD_MASK; // OUTMODE:0
        TA0CCTL1 |= TIMER_A_CCTLN_OUT;          // OUT:1
        TA0CTL |= TIMER_A_CTL_CLR;              // CLEAR
        return 0;
    }
    // duty out of (0,100)
    else if (duty < 0 || duty > 100)
    {
        TA0CCTL1 &= ~TIMER_A_CCTLN_OUT;         // SET OUT 0
        TA0CCTL1 &= ~TIMER_A_CCTLN_OUTMOD_MASK; // OUTPUT MODE : 0
        TA0CTL |= TIMER_A_CTL_CLR;
        return 1;
    }
    else if (5 < duty || duty < 95)
    {
        TA0CCR0 = 7500;
        TA0CCR1 = count;
        TA0CTL |= TIMER_A_CTL_CLR;
        TA0CCTL1 &= ~TIMER_A_CCTLN_OUTMOD_MASK;
        TA0CCTL1 |= TIMER_A_CCTLN_OUTMOD_7; // OUTPUT MODE:7
        return 0;
    }
}
