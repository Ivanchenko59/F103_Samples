#include "tim.h"

/**
*@brief Configurate TIM1_CH1 to PA8
*Output 2MHz alt. function push-pull
*/
void TIM1_CH1_GPIO_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);
	GPIOA->CRH |= (GPIO_CRH_MODE8_1 | GPIO_CRH_CNF8_1);
	
	
}

/**
*@brief TIM1 Output compare configuration
*/
void TIM1_OC_init(uint32_t ms)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	//Upcounting
	TIM1->CR1 &= ~TIM_CR1_DIR;	
	//One pulse mode off (periodic mode)
	TIM1->CR1 &= ~TIM_CR1_OPM;
	//Reset mode 						why? idk
	TIM1->CR2 &= ~TIM_CR2_MMS;
	TIM1->PSC = (ms * 10) - 1;
	TIM1->ARR = 7200 - 1;				//10 kHz
	TIM1->SR &= ~TIM_SR_UIF;			//clear interrupt flag
	
	/*Output compare channel - TIM1_CH1*/
	//Disable OC
	TIM1->CCER = 0;
	//Config as output
	TIM1->CCMR1 &= ~TIM_CCMR1_CC1S;
	//Toggle output
	TIM1->CCMR1 |= TIM_CCMR1_OC1M;
	TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_2;
	//Polarity active low
	TIM1->CCER &= ~TIM_CCER_CC1P;
	//Counter value to toggle out
	TIM1->CCR1 = 10;
	//Enable CH1
	TIM1->CCER |= TIM_CCER_CC1E;
	//Slave controller reset			//why? idk
	TIM1->SMCR = 0;	
	//Enable MOE
	TIM1->BDTR |= TIM_BDTR_MOE;
	//Enable timer
	TIM1->CR1 |= TIM_CR1_CEN;
}
