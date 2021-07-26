#include "main.h"
#include "led.h"

volatile uint32_t tick_delay = 0;

int main(void) 
{
	mcu_init();
	led_init();
	
	while(1) {
	
		led_toggle();
		delay(1000);
	}
	
}

void mcu_init(void)
{
	SysTick_Config(SystemCoreClock / 1000);
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
