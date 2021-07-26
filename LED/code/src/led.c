#include "led.h"

void led_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13_0);
	GPIOC->CRH |= GPIO_CRH_MODE13_1;
}

void led_write(uint8_t state)
{
	if(state) {
		GPIOC->ODR |= GPIO_ODR_ODR13;
	}
	else {
		GPIOC->ODR &= ~GPIO_ODR_ODR13;
	}

}

void led_toggle(void)
{
	GPIOC->ODR ^= GPIO_ODR_ODR13;
}
