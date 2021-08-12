#include "i2c.h"

/**
*@brief I2C GPIO pins configuration
*/
void i2c_I2C1_GPIO_config(void)
{
	//PB8 - SCL, PB9 - SDA
	//Alternative mapping
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;
	//Enable Port B clock
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	//Mode: Output 10 MHz
	GPIOB->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_MODE9);
	GPIOB->CRH |= GPIO_CRH_MODE8_0 | GPIO_CRH_MODE9_0;
	//CNF: Alternative function Open-Drain
	GPIOB->CRH |= GPIO_CRH_CNF8 | GPIO_CRH_CNF9;
}

/**
*@brief I2C Peripheral configuration
*/
void i2c_I2C1_config(void)
{
	//Enable I2C Clock
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	//Tell I2C register APB1 Clock Frequency
	I2C1->CR2 &= ~(I2C_CR2_FREQ);
	I2C1->CR2 = 36;
	//Rise Time
	I2C1->TRISE = 36 + 1;
	//I2C Speed (100kHz)
		/*
			T_high = CCR * T_pclk1
			T_low = CCR * T_pclk1
	
			T = T_high + T_low
			T = 100 kHz = 10 us
			T_high = T_low = T / 2 = 10 us / 2 = 5 us
			
			T_pclk1 = 36 MHz = 0.02777 us
	
			CCR = T_high / T_pclk1 = 5 / 0.2777 = ~180
		*/
	I2C1->CCR = 180;	//100kHz SCL
	//Enable I2C peripheral
	I2C1->CR1 |= I2C_CR1_PE;
}

/**
*@brief I2C Check Address
*/
uint8_t i2c_I2C1_isSlaveAdressExist(uint8_t addrs, uint32_t timeout)
{
	uint32_t init_ticks = sys_tick;
	//Send Start condition
	I2C1->CR1 &= ~I2C_CR1_POS;
	I2C1->CR1 |= I2C_CR1_START;
	
	while (!(I2C1->SR1 & I2C_SR1_SB)) {
		if((sys_tick - init_ticks) > timeout) {
			return 1;
		}
	}
	//Send Slave Address
	I2C1->DR = addrs;
	//Wait for ACK
	while (!(I2C1->SR1 & I2C_SR1_ADDR)) {
		if((sys_tick - init_ticks) > timeout) {
			return 1;
		}
	}
	//Generate Stop condition
	I2C1->CR1 |= I2C_CR1_STOP;
	//Clear ADDRS Flag
	__IO uint32_t tempRd = I2C1->SR1;
	tempRd = I2C1->SR2;
	(void)tempRd;
	//Wait for I2C busy
	while ((I2C1->SR1 & I2C_SR2_BUSY)) {
		if((sys_tick - init_ticks) > timeout) {
			return 1;
		}
	}
	/* Return 0, everything ok */
	return 0;
}

/**
*@brief I2C Transmit (Master)
*/
uint8_t i2c_I2C1_masterTransmit(uint8_t addrs, uint8_t *pData, uint8_t len, uint32_t timeout);

/**
*@brief I2C Receive (Master)
*/
uint8_t i2c_I2C1_masterReceive(uint8_t addrs, uint8_t *pData, uint8_t len, uint32_t timeout);
