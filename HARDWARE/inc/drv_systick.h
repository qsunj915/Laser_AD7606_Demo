#ifndef __DRV_SYSTICK_H
#define __DRV_SYSTICK_H

#include "stm32f4xx.h"

extern uint32_t E_COUNTER;

void SysTick_Init(void);
void delay_us(u32 time);
void delay_ms(u32 time);


#endif

