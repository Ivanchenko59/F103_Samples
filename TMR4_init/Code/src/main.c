#include "main.h"

int main(void) 
{
	mcu_init();
	led_init();
	TIM4_init();
	
	while(1) {
	
	}
	
}

void mcu_init() 
{
	SysTick_Config(SystemCoreClock/1000);
}	


void TIM4_init(void) 
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;			//clocking TIM4
	
	/*-----------------------------------------------------------------------------------
	
	TIM freq. = periph. clock / Prescaller / ARR = periph. clk. / (PSC * ARR)
	or VALUE = PSC * ARR = Periph clk / Desired TIM freq
	
	TIM_CNT go from 0 to ARR, becouse that, i need to setup ARR > 0
	ARR-------------------
	 .        /       /
	 .      /  |    /  |
	 .    /    |  /    |
	 0  /CNT   |/CNT   |
	
	-----------------------------------------------------------------------------------*/
	
	TIM4->PSC = 64000 - 1; 						//devide f_clk
	TIM4->ARR = 1125 - 1;						//reload value
	
	TIM4->DIER |= TIM_DIER_UIE;					//update interrupt enable
	NVIC_EnableIRQ(TIM4_IRQn);					//enable irq
	TIM4->CR1 |= TIM_CR1_CEN;					//start timer
}

void led_init(void) 
{
    // turn on GPIOA clocking
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    // set gpio pin mode
    GPIOC->CRH &= ~GPIO_CRH_MODE13_0; // set as
    GPIOC->CRH |= GPIO_CRH_MODE13_1;  // output with 2 MHz speed
    GPIOC->CRH &= ~GPIO_CRH_CNF13;    // set as push-pull output
}

void TIM4_IRQHandler (void) 
{
	TIM4->SR &= ~TIM_SR_UIF; // сбрасываем прерывание
	GPIOC->ODR ^= GPIO_ODR_ODR13;
}
