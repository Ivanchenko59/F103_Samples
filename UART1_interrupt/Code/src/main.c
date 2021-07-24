#include "main.h"

int main(void) 
{
	UART1_init();
	
	while(1) {
	
	
	}
	
}

void UART1_init(void)
{ 
	//clock USART1 / GPIOA /ALT. FUNC
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;

	//GPIOA_9 Alternate function output Push-pull for TX
	GPIOA->CRH  &= ~GPIO_CRH_CNF9;                              
	GPIOA->CRH  |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0;

	//GPIOA_10 Input with pull-up / pull-down for RX
	GPIOA->CRH  &= ~GPIO_CRH_CNF10;
	GPIOA->CRH  |= GPIO_CRH_CNF10_1;
	GPIOA->CRH  &= ~GPIO_CRH_MODE10;

	/*-------------------------------------------------------------
	BAUD = Fclk / (16 * USARTDIV)
	USARTDIV = Fclk / (16 * BAUD)
	USARTDIV = 72000000 / (16 * 9600) = 468.75
	Mantisa 468 = 0x1D4
	Fraction 16*0.75 = 12 = 0xC
	BRR = 0x1D4C
	-------------------------------------------------------------*/
	USART1->BRR = 0x1D4C;    
	
	//enable RXNE and TXE interrupts on USART SIDE
	USART1->CR1 |= USART_CR1_RXNEIE | USART_CR1_TXEIE;
	
	/*-------------------------------------------------------------
	USART_CR1_RE - receiver enable
	USART_CR1_TE - transmitter enable
	USART_CR1_UE - USART enable
	-------------------------------------------------------------*/
	USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
	
	NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void) 
{

	//check if we are here because of RXNE interrupt
	if (USART1->SR & USART_SR_RXNE) {						//if RX is not empty
	
		char temp = USART1->DR; 							//fetch the data received
		USART1->DR = temp;  								//send it back out
		while (!(USART1->SR & USART_SR_TC))
		;

	}

	//check if we are here because of TXEIE interrupt
	if (USART1->SR & USART_SR_TXE) {						//if RX is not empty
		//handle transmit completion here
	}

}
