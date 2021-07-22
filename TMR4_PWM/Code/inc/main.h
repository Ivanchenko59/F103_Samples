#ifndef __MAIN_H__
#define __MAIN_H__
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stm32f10x.h"

void delay(const uint32_t milliseconds);
volatile uint32_t ticks_delay = 0;

void mcu_init(void);
void TIM4_init(void);
#endif /* __MAIN_H__ */
