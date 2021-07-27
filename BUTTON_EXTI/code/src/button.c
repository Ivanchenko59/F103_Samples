#include "button.h"

void button_init(void)
{ 
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//Input with pull-up/pull-down
	GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0_0);
	GPIOA->CRL |= GPIO_CRL_CNF0_1;
	//Pull-down
	GPIOA->CRL &= ~GPIO_ODR_ODR0;
}
