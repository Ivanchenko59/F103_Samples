#include "main.h"
#include "tim.h"
int main(void) 
{	
	TIM3_PWM_GPIO_init();
	TIM3_PWM_init();
	
	while(1) {
	
		set_RGB(255, 255, 0);
		
	}
}
