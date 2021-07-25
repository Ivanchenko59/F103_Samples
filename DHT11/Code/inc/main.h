#ifndef __MAIN_H__
#define __MAIN_H__
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stm32f10x.h"

void delay(const uint32_t us);

void mcu_init(void);

void DHT11_start(void);
int8_t DHT11_Response(void);
uint8_t DHT11_Read(void);

#endif /* __MAIN_H__ */
