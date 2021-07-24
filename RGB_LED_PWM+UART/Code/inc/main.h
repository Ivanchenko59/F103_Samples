#ifndef __MAIN_H__
#define __MAIN_H__
#include "stm32f10x.h"

void mcu_init(void);
void UART1_init(void);
void TIM4_init(void);
void delay(const uint32_t milliseconds);
#endif /* __MAIN_H__ */
