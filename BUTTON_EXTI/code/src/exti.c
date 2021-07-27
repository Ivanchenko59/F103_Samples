#include "exti.h"

void button_exti_init(void)
{ 
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;
	//PA0 maps EXTI0
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;
	EXTI->FTSR |= EXTI_FTSR_TR0;
	EXTI->RTSR &= ~EXTI_RTSR_TR0;	
	//Unlock EXTI0 interrupt
	EXTI->IMR |= EXTI_IMR_MR0;
	
	NVIC_SetPriority(EXTI0_IRQn, 5);
	NVIC_EnableIRQ(EXTI0_IRQn);
}
