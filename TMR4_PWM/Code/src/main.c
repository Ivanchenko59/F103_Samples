/*INIT PWM AND TEST SERVO (SERVO NEED 50 HZ FREQ. AND DUTY CYCLE 2 - 12%)*/
#include "main.h"

#define PERIOD(F) (1e6/F)
#define FREQ 50
uint16_t DUTY = 10;
int main(void) 
{
	mcu_init();
	TIM4_init();
	
	while(1) {
		delay(200);
		DUTY += 1;
		if (DUTY > 13) DUTY = 2;
		TIM4->CCR4 = PERIOD(FREQ) / 100 * DUTY - 1;
	}
	
}

void delay(const uint32_t milliseconds) 
{
    uint32_t start = ticks_delay;
    while((ticks_delay - start) < milliseconds);
}

void mcu_init() 
{
	SysTick_Config(SystemCoreClock/1000);
}	


void TIM4_init(void) 
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;			//clocking GPIOB
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; 		//alt. function
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;			//clocking TIM4
	
	//GPIOB9 alt. func for TIM4 CHANNEL4
	GPIOB->CRH &= ~GPIO_CRH_CNF9;
    GPIOB->CRH |= GPIO_CRH_CNF9_1;
    GPIOB->CRH |= GPIO_CRH_MODE9;
	/*-----------------------------------------------------------------------------------
	
	TIM freq. = periph. clock / Prescaller / ARR = periph. clk. / (PSC * ARR)
	or VALUE = PSC * ARR = Periph clk / Desired TIM freq
	
	CCR control duty cycle. When CCR = ARR duty is 100%, when CCR = 0, duty = 0%
	
	ARR-------------------
	 .        /       /
	CCR-----/--|----/--|
	 .    /    |  /    |
	 0  /CNT   |/CNT   |
	
	_______     ___     ___
	       |   |   |   |
	       |___|   |___|
	-----------------------------------------------------------------------------------*/
	
	TIM4->CCER |= TIM_CCER_CC4E;
	TIM4->CR1 |= TIM_CR1_ARPE;
	
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;	//PWM mode 1
	TIM4->CCMR2 |= TIM_CCMR2_OC4PE;						//preloader
	
	TIM4->PSC = 72 - 1;									//devide f_clk
	TIM4->ARR = PERIOD(FREQ) - 1;						//reload value
	TIM4->CCR4 = PERIOD(FREQ) / 100 * DUTY - 1;
	
	TIM4->EGR |= TIM_EGR_UG;
	TIM4->CR1 |= TIM_CR1_CEN;							//start timer
}

void SysTick_Handler(void) {
  ticks_delay++;
}
