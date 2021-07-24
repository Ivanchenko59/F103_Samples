#include "main.h"

int main(void) 
{
	UART1_init();
	
	while(1) {
		if (USART1->SR & USART_SR_RXNE) 						//if RX is not empty
		{
			char temp = USART1->DR; 							//fetch the data received
			USART1->DR = temp;  								//send it back out
			while (!(USART1->SR & USART_SR_TC)) 				//wait for TX to be complete
			;
		}
	}
	
}

void UART1_init(void)
{ 
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;                       //enable USART1
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;							//clock GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;                         //enable alternative function IO clock

	//GPIOA_9 Alternate function output Push-pull for TX
	GPIOA->CRH  &= ~GPIO_CRH_CNF9;                              
	GPIOA->CRH  |= GPIO_CRH_CNF9_1;
	GPIOA->CRH  |= GPIO_CRH_MODE9_0;

	//GPIOA_10 Input with pull-up / pull-down for RX
	GPIOA->CRH  &= ~GPIO_CRH_CNF10;
	GPIOA->CRH  |= GPIO_CRH_CNF10_1;
	GPIOA->CRH  &= ~GPIO_CRH_MODE10;
	//GPIOA->BSRR |= GPIO_ODR_ODR10;
	/*-------------------------------------------------------------
	BAUD = Fclk / (16 * USARTDIV)
	USARTDIV = Fclk / (16 * BAUD)
	USARTDIV = 72000000 / (16 * 9600) = 468.75
	Mantisa 468 = 0x1D4
	Fraction 16*0.75 = 12 = 0xC
	BRR = 0x1D4C
	-------------------------------------------------------------*/
	USART1->BRR = 0x1D4C;    
	
	/*-------------------------------------------------------------
	USART_CR1_RE - receiver enable
	USART_CR1_TE - transmitter enable
	USART_CR1_UE - USART enable	(ENABLE LAST!)
	-------------------------------------------------------------*/
	USART1->CR1 |= USART_CR1_RE;
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_UE;
}
