#include "main.h"
#include "button.h"
#include "exti.h"

volatile uint32_t tick_delay = 0;
uint8_t btn_exti_flag = 0;

int main(void) 
{
	mcu_init();
	button_init();
	button_exti_init();
	
	while(1) {
		if (btn_exti_flag) {
			btn_exti_flag = 0;
			//something to do.
		}
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

void EXTI0_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(EXTI0_IRQn);
	EXTI->PR |= EXTI_PR_PR0;
	btn_exti_flag = 1;
}
