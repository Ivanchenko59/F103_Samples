#ifndef __TIM_H__
#define __TIM_H__
#include "main.h"

/**
*@brief Configurate GPIO PWM 
*CH1 - PA6, CH2 - PA7, CH3 - PB0
*Speed 2 MHz, alternative push-pull
*/
void TIM3_PWM_GPIO_init(void);

/**
*@brief Configurate TIM3 PWM mode
*/
void TIM3_PWM_init(void);

/**
*@brief PWM duty cycle RBG (0 - 255)
*/
void set_RGB(uint8_t R, uint8_t G, uint8_t B);

#endif /* __TIM_H__ */
