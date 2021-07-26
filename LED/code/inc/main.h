#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f10x.h"

void mcu_init(void);

/**
*@brief Creating a delay
*
*@param ms Delay time in ms
*/
void delay(uint32_t ms);

#endif /* __MAIN_H__ */
