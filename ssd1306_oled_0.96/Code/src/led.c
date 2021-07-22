#include "led.h"

void led_init() {
	
	GPIOB->CRL &= ~GPIO_CRL_CNF0;	
	GPIOB->CRL |= GPIO_CRL_MODE0;
	
	GPIOB->CRL &= ~GPIO_CRL_CNF1;
	GPIOB->CRL |= GPIO_CRL_MODE1;
	
	GPIOC->CRH &= ~GPIO_CRH_CNF13;	
	GPIOC->CRH |= GPIO_CRH_MODE13;
	
}

void led_0_on(void) {
	GPIOB->ODR |= GPIO_ODR_ODR0;
}

void led_0_off(void) {
	GPIOB->ODR &= ~GPIO_ODR_ODR0;
}

void led_0_toggle(void) {
	GPIOB->ODR ^= GPIO_ODR_ODR0;
}

void led_1_on(void) {
	GPIOB->ODR |= GPIO_ODR_ODR1;
}

void led_1_off(void) {
	GPIOB->ODR &= ~GPIO_ODR_ODR1;
}

void led_1_toggle(void) {
	GPIOB->ODR ^= GPIO_ODR_ODR1;
}


void led_3_off(void) {
	GPIOC->ODR |= GPIO_ODR_ODR13;
}

void led_3_on(void) {
	GPIOC->ODR &= ~GPIO_ODR_ODR13;
}

void led_3_toggle(void) {
	GPIOC->ODR ^= GPIO_ODR_ODR13;
}
