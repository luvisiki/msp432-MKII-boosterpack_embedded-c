/*
 * timer.h
 *
 *  Created on: 2023年3月30日
 *      Author: luvisiki
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>

void config_blue_pwm(void);
void config_red_green_pwm(void);
uint8_t pwm_blue(uint8_t duty);
uint8_t pwm_red(uint8_t duty);
uint8_t pwm_green(uint8_t duty);


#endif /* TIMER_TIMER_H_ */
