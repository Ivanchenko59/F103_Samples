#include "main.h"
#include "button.h"

volatile uint32_t tick_delay = 0;
uint8_t state;

int main(void) 
{
	mcu_init();
	button_init();
	
	while(1) {
		state = button_read();
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
