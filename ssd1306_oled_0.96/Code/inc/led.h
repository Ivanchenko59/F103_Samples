#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"

void led_init(void);

void led_0_on(void);
void led_0_off(void);
void led_0_toggle(void);

void led_1_on(void);
void led_1_off(void);
void led_1_toggle(void);

void led_3_on(void);
void led_3_off(void);
void led_3_toggle(void);

#endif /* __LED_H__ */
