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
    //configure blue LED DIo
    P5->DIR |= BIT6;
    P5->SEL0 |= BIT6;
    P5->SEL1 &= ~BIT6;

    TA2CTL = 0;
    TA2CCR0 = 7500;                             //24MHz / 4 /800hz = 7500
    TA2CCR1 = 1875;                             //duty cycle for 25%: 7500/4 = 1875
    TA2CTL |= (TIMER_A_CTL_SSEL__SMCLK |        //use SMCLK clock:24MHz
                TIMER_A_CTL_MC__UP |            //Up mode: Timer counts up to TAxCCR0
                TIMER_A_CTL_ID__4 |             //use divided 4
                TIMER_A_CTL_CLR);               //TimerA clear

    TA2CCTL1 |= TIMER_A_CCTLN_OUTMOD_7;         //mode 7
}

