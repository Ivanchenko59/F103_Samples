#ifndef __I2C_H__
#define __I2C_H__

#include "main.h"

/**
*@brief I2C GPIO pins configuration
*/
void i2c_I2C1_GPIO_config(void);

/**
*@brief I2C Peripheral configuration
*/
void i2c_I2C1_config(void);

/**
*@brief I2C Check Address
*/
uint8_t i2c_I2C1_isSlaveAdressExist(uint8_t addrs, uint32_t timeout);

/**
*@brief I2C Transmit (Master)
*/
uint8_t i2c_I2C1_masterTransmit(uint8_t addrs, uint8_t *pData, uint8_t len, uint32_t timeout);

/**
*@brief I2C Receive (Master)
*/
uint8_t i2c_I2C1_masterReceive(uint8_t addrs, uint8_t *pData, uint8_t len, uint32_t timeout);

#endif /*__I2C_H__*/
