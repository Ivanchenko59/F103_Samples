#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f10x.h"

#define DIGIT_PORT	GPIOB
#define DIGIT_CLK	(1UL << 10)
#define DIGIT_DIO	(1UL << 11)


void mcu_init(void);
void tm1637_gpio_config(void);
/**
*@brief Creating a delay
*
*@param ms Delay time in ms
*/
extern void delay(uint32_t ms);

#endif /* __MAIN_H__ */
