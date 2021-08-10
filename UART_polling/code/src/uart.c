#include "uart.h"

/**
*@brief UART1 GPIO Configuration
*/
void UART1_GPIO_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_CNF10 | GPIO_CRH_MODE9 | GPIO_CRH_MODE10);
	GPIOA->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1 | GPIO_CRH_MODE9_0;
}

/**
*@brief UART1 Peripheral Configuration
*/
void UART1_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	//Enable Transmit
	USART1->CR1 |= USART_CR1_TE;
	//Enable Receive
	USART1->CR1 |= USART_CR1_RE;
	//Parity to Even
	USART1->CR1 &= ~USART_CR1_PS;
	//Parity control enabled
	USART1->CR1 &= ~USART_CR1_PCE;
	//Word lenght to 8-bits
	USART1->CR1 &= ~USART_CR1_M;
	//Stop bit to 1
	USART1->CR2 &= ~USART_CR2_STOP;
	//Disable HW Flow Control
	USART1->CR3 &= ~USART_CR3_CTSE;
	USART1->CR3 &= ~USART_CR3_RTSE;
	//Set Baud rate to 115200
	USART1->BRR |= 625;
	//Clear some flag and enable
	USART1->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
	USART1->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);
	//Enable UART
	USART1->CR1 |= USART_CR1_UE;
}

/**
*@brief UART1 Transmit
*/
uint8_t UART1_transmit(uint8_t *data, uint8_t len, uint32_t timeout)
{
	//Wain on TXE to start transmit
	//Write to DR as TXE flag is HIGH (TX buffer empty)
	uint8_t data_idx = 0;
	uint32_t start_tick = sys_tick;
	
	while (data_idx < len) {
		if (USART1->SR & USART_SR_TXE) {			//TX buffer empty
			USART1->DR = data[data_idx];
			data_idx++;
		}
		else {
			if (sys_tick - start_tick >= timeout) {
				return 1;
			}
		}
	}
	
	//Wait for busy flag
	while (USART1->SR & USART_SR_TC) {
		if (sys_tick - start_tick >= timeout) {
			return 1;
		}
	}
	return 0;
}

/**
*@brief UART1 Receive
*/
uint8_t UART1_receive(uint8_t *data, uint8_t len, uint32_t timeout)
{
	uint8_t data_remain = len;
	uint32_t start_tick = sys_tick;
	
	while (data_remain > 0) {
		if (USART1->SR & USART_SR_RXNE) {
			*data++ = (uint8_t)(USART1->DR & 0xFF);
			data_remain--;
		}
		else {
			if (sys_tick - start_tick >= timeout) {
				return 1;
			}
		}
	}
	return 0;
}
