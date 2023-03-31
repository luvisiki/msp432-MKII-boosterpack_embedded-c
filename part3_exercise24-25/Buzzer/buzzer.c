/*
 * buzzer.c
 *
 *  Created on: 2023.3.31
 *      Author: luvisiki
 */

#include <stdint.h>
#include "buzzer.h"

static uint16_t buzzer_flag, count;

void config_buzzer(void)
{
    buzzer_flag = 0;
    count = 0;
    // configure DIO
    P2->DIR |= BIT7;
    P2->SEL0 &= ~BIT7;
    P2->SEL1 &= ~BIT7;
    P2->OUT |= BIT7;
    // CONFIGURE TIMER
    TA1CCR0 = 60000;
    TA1CCTL0 &= ~TIMER_A_CCTLN_OUTMOD_MASK;               // OUT:0
    TA1CCTL0 |= TIMER_A_CCTLN_CCIE | TIMER_A_CCTLN_CCIFG; // INTERRUPT
    TA1CTL |= (TIMER_A_CTL_SSEL__SMCLK |
               TIMER_A_CTL_CLR |
               TIMER_A_CTL_ID__4 |
               TIMER_A_CTL_MC__UP);
    NVIC_EnableIRQ(TA1_0_IRQn);
}

void buzzer_stop(void)
{
    buzzer_flag = 0;
    count = 0;
    P2->OUT |= BIT7;
    TA1CTL |= TIMER_A_CTL_CLR;
}

uint8_t buzzer_play(int tone, int duration)
{
    if (buzzer_flag == 0)
    {
        count = 0;
        TA1CCR0 = 6000000 / tone / 2;
        buzzer_flag = tone * 2 * duration / 1000;
        TA1CTL |= TIMER_A_CTL_CLR;
        return 1;
    }
    return 0;
}

// interrupt
extern void TA1_0_IRQHandler(void)
{
    if (buzzer_flag>0)
    {
        P2->OUT ^= BIT7; // traggle
        if (++count > buzzer_flag)
        {
            buzzer_flag = 0;
            count = 0;
            P2->OUT |= BIT7;
        }
    }
    // CLEAR
    TA1CCTL0 &= ~(TIMER_A_CCTLN_CCIFG | TIMER_A_CCTLN_COV);
    TA1CTL |= TIMER_A_CTL_CLR;
}