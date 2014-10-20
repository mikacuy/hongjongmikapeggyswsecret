#ifndef __TICKS_H
#define __TICKS_H

#include "stm32f10x_tim.h"
#include "buzzer.h"

extern volatile u16 ticks;
extern volatile u16 seconds;

typedef struct {
	u16 ticks, seconds;
} TIME;

void ticks_init(void);
u16 get_ticks(void);
u16 get_seconds(void);
TIME get_time(void);

void buzzer_control(u8 count, u16 period);

__attribute__((__interrupt__))
void SysTick_Handler(void);

#endif		/*  __TICKS_H */
