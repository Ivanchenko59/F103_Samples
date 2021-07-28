#ifndef __TIM_H__
#define __TIM_H__
#include "main.h"

/**
*@brief Delay timer configuration - TIM2
*/
void TIM2_init(void);

/**
*@brief timer for switch LED digit configuration - TIM4
*/
void TIM4_init(void);

/**
*@brief ms delay
*/
void _msDelay(uint32_t ms);

#endif /* __TIM_H__ */
