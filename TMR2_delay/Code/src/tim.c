#include "tim.h"

void TIM2_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//Upcounting
	TIM2->CR1 &= ~TIM_CR1_DIR;	
	//One pulse mode 
	//Counter stops counting at the next update event (clearing the bit CEN)
	TIM2->CR1 |= TIM_CR1_OPM;
	
	TIM2->PSC = 0;
	TIM2->ARR = 7200 - 1;				//10 kHz
}

void _msDelay(uint32_t ms)
{
	TIM2->PSC = (ms * 10) - 1;
	TIM2->CR1 |= TIM_CR1_CEN;			//start timer
	while(!(TIM2->SR & TIM_SR_UIF));	//wait interrupt flag
	TIM2->SR &= ~TIM_SR_UIF;			//clear interrupt flag
}
