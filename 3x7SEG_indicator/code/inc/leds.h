#ifndef __LEDS_H__
#define __LEDS_H__

#include "main.h"

static uint8_t digitsToSegment[10] =
{
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F,
};

void LEDS_gpio_init(void);
void writeDigits(uint8_t digitsData[4]);

#endif /* __LEDS_H__ */
