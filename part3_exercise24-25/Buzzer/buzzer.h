/*
 * buzzer.h
 *
 *  Created on: 2023.3.31
 *      Author: luvisiki
 */

#ifndef BUZZER_BUZZER_H_
#define BUZZER_BUZZER_H_


#include <stdint.h>
#include "msp.h"

uint8_t buzzer_play(int tone,int duration);
void config_buzzer(void);
void buzzer_stop(void);



#endif /* BUZZER_BUZZER_H_ */
