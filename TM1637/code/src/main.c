#include "main.h"
#include "tm1637.h"

volatile uint32_t tick_delay = 0;
uint8_t state;

int main(void) 
{
	mcu_init();
	tm1637_gpio_config();
	tm1637_init(DIGIT_PORT, DIGIT_CLK, DIGIT_DIO);
	
	while(1) {
		uint8_t digitsData[4] = {1, 2, 3, 4};
		tm1637_writeDigits(digitsData, 1);
	}
	
}

void mcu_init(void)
{
	SysTick_Config(SystemCoreClock / 1000);
}

void tm1637_gpio_config(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRH |= GPIO_CRH_MODE10_1 | GPIO_CRH_MODE11_1;
	GPIOB->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_CNF11 | GPIO_CRH_MODE10_0 | GPIO_CRH_MODE11_0);
}

void delay(const uint32_t ms) 
{
	uint32_t start = tick_delay;
	while((tick_delay - start) < ms);
}

void SysTick_Handler(void)
{
	tick_delay++;
}
