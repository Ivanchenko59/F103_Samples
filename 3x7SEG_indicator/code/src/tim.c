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

void TIM4_init(void) 
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;			//clocking TIM4

	TIM4->PSC = 64000 - 1; 						//devide f_clk
	TIM4->ARR = 1125 - 1;						//reload value
	
	TIM4->DIER |= TIM_DIER_UIE;					//update interrupt enable
	NVIC_EnableIRQ(TIM4_IRQn);					//enable irq
	TIM4->CR1 |= TIM_CR1_CEN;					//start timer
}
