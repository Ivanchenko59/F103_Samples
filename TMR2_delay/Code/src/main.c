#include "main.h"
#include "tim.h"
int main(void) 
{
	led_init();
	TIM2_init();
	
	while(1) {
		GPIOC->ODR |= GPIO_ODR_ODR13;
		_msDelay(1000);
		GPIOC->ODR &= ~GPIO_ODR_ODR13;
		_msDelay(1000);
	}
	
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
