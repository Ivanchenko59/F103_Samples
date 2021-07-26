#ifndef __LED_H__
#define __LED_H__

#include "main.h"

/**
*@brief LED gpio PC13 configuration
*/
void led_init(void);

/**
*@brief Set ON/OFF LED
*
*@param state Write 0 / 1 to turn ON / OFF the LED
*/
void led_write(uint8_t state);

/**
*@brief Reverses the LED value
*/
void led_toggle(void);

#endif /* __LED_H__ */
