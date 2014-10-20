#ifndef __BUZZER_H
#define __BUZZER_H

#include "stm32f10x.h"

#define BUZZER_PORT GPIOF
#define BUZZER_PIN	GPIO_Pin_0
#define BUZZER_RCC	RCC_APB2Periph_GPIOF


void buzzer_init(void);	 						//init
void buzzer_set(u8 state);						// 1: on, 0: off

#endif /* __BUZZER_H */
