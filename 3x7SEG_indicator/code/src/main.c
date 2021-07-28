#include "main.h"
#include "leds.h"
#include "tim.h"
uint8_t i = 0;
int main(void)
{

	TIM2_init();
	TIM4_init();
	LEDS_gpio_init();
	
	while(1) {	
		uint8_t digitsData[3] = {5,2,8};
		writeDigits(digitsData);
	}
}


void TIM4_IRQHandler (void) 
{
	TIM4->SR &= ~TIM_SR_UIF;
}
