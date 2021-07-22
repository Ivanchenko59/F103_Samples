#ifndef __UTILS_H__
#define __UTILS_H__

#include "stm32f10x.h"

extern volatile uint32_t ticks_delay;

void clocking_init(void);
void delay(uint32_t milliseconds);

#endif /* __UTILS_H__ */
