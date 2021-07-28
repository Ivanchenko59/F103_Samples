#ifndef __TIM_H__
#define __TIM_H__
#include "main.h"

/**
*@brief Configurate TIM1_CH1 to PA8
*/
void TIM1_CH1_GPIO_init(void);

/**
*@brief TIM1 Output compare configuration
*/
void TIM1_OC_init(uint32_t ms);

#endif /* __TIM_H__ */
