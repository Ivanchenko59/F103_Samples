#ifndef __TM1637_H__
#define __TM1637_H__

#include "main.h"

/**
*@brief configuration GPIO for TM1637 LED display
*/
void tm1637_init(GPIO_TypeDef *port, uint16_t clkPin, uint16_t dioPin);

void tm1637_writeDigits(uint8_t digitsData[4], uint8_t colomn);

void tm1637_setBrightness(uint8_t value_0_7);

void tm1637_setCounter(uint16_t counter);

void tm1637_setClock(uint8_t hrs, uint8_t mins);

#endif /* __TM1637_H__ */
