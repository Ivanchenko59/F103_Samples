#ifndef __UART_H__
#define __UART_H__

#include "main.h"

/**
*@brief UART1 GPIO Configuration
*/
void UART1_GPIO_init(void);

/**
*@brief UART1 Peripheral Configuration
*/
void UART1_init(void);

/**
*@brief UART1 Transmit
*/
uint8_t UART1_transmit(uint8_t *data, uint8_t len, uint32_t timeout);

/**
*@brief UART1 Receive
*/
uint8_t UART1_receive(uint8_t *data, uint8_t len, uint32_t timeout);

#endif /*__UART_H__*/
