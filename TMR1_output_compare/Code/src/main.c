#include "main.h"
#include "tim.h"
int main(void) 
{	
	//PA8 led toggle
	TIM1_CH1_GPIO_init();
	TIM1_OC_init(1000);
	
	while(1) {
	
	}
}
