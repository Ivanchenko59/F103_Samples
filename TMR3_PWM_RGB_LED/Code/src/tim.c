#include "tim.h"

/**
*@brief Configurate GPIO PWM
*CH1 - PA6, CH2 - PA7, CH3 - PB0
*Speed 2 MHz, alternative push-pull
*/
void TIM3_PWM_GPIO_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
	GPIOA->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_CNF7 | GPIO_CRL_MODE6 | GPIO_CRL_MODE7);
	GPIOA->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1 | GPIO_CRL_MODE6_1 | GPIO_CRL_MODE7_1;
	GPIOB->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	GPIOB->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0_1;
}

/**
*@brief Configurate TIM3 PWM mode
*/
void TIM3_PWM_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	//Count up
	TIM3->CR1 &= ~TIM_CR1_DIR;
	//Periodic mode
	TIM3->CR1 &= ~TIM_CR1_OPM;
	//Reset mode
	TIM3->CR2 &= ~TIM_CR2_MMS;
	//Prescaler
	TIM3->PSC = 0;
	//Period 10 kHz
	TIM3->ARR = 1000 - 1;
	//Clear update interrupt
	TIM3->SR &= ~TIM_SR_UIF;
	
	//Disable OC
	TIM3->CCER = 0;
	
	//CH1
	//Set mode output
	TIM3->CCMR1 &= ~TIM_CCMR1_CC1S;
	//PWM mode
	TIM3->CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	//Polarity
	TIM3->CCER &= ~TIM_CCER_CC1P;
	//Set duty cycle
	TIM3->CCR1 = 0;
	
	//CH2
	//Set mode output
	TIM3->CCMR1 &= ~TIM_CCMR1_CC2S;
	//PWM mode
	TIM3->CCMR1 &= ~TIM_CCMR1_OC2M;
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
	//Polarity
	TIM3->CCER &= ~TIM_CCER_CC2P;
	//Set duty cycle
	TIM3->CCR2 = 0;
	
	//CH3
	//Set mode output
	TIM3->CCMR2 &= ~TIM_CCMR2_CC3S;
	//PWM mode
	TIM3->CCMR2 &= ~TIM_CCMR2_OC3M;
	TIM3->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
	//Polarity
	TIM3->CCER &= ~TIM_CCER_CC3P;
	//Set duty cycle
	TIM3->CCR3 = 0;

	//Enable channels 
	TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E;

	//Start TIM3
	TIM3->CR1 |= TIM_CR1_CEN;
}

/**
*@brief PWM duty cycle RBG (0 - 255)
*/
void set_RGB(uint8_t R, uint8_t G, uint8_t B)
{
	TIM3->CCR1 = (uint16_t)((TIM3->ARR + 0.0f) * (R / 255.0f));
	TIM3->CCR2 = (uint16_t)((TIM3->ARR + 0.0f) * (G / 255.0f));
	TIM3->CCR3 = (uint16_t)((TIM3->ARR + 0.0f) * (B / 255.0f));
}
