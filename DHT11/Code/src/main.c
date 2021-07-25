#include "main.h"

volatile uint32_t ticks_delay = 0;
uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
uint16_t RH, TEMP;

int main(void) 
{	
	mcu_init();
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	
	while(1) {
	
		DHT11_start();
		DHT11_Response();
		Rh_byte1 = DHT11_Read();
		Rh_byte2 = DHT11_Read();
		Temp_byte1 = DHT11_Read();
		Temp_byte2 = DHT11_Read();
		TEMP = Temp_byte1;
		RH = Rh_byte1;
		delay(2000000);
	}
}

void DHT11_start(void) 
{
	//GPIO as output
	GPIOB->CRL &= ~GPIO_CRL_CNF1_1;
	GPIOB->CRL |= GPIO_CRL_CNF1_0;
	GPIOB->CRL |= GPIO_CRL_MODE1;
	GPIOB->ODR &= ~GPIO_ODR_ODR1;
	delay(20000);
	//GPIO as input
	GPIOB->CRL |= GPIO_CRL_CNF1_0;
	GPIOB->CRL &= ~GPIO_CRL_CNF1_1;
	GPIOB->CRL &= ~GPIO_CRL_MODE1;
}

int8_t DHT11_Response(void)
{
	int8_t Response = 0;
	delay (40);
	if (!(GPIOB->IDR & GPIO_IDR_IDR1)){
		delay (80);
		if (GPIOB->IDR & GPIO_IDR_IDR1) {
			Response = 1;
		}
		else { 
			Response = -1;
		}
	}
	while (GPIOB->IDR & GPIO_IDR_IDR1);  			// wait for the pin to go low

	return Response;
}

uint8_t DHT11_Read(void)
{
	uint8_t i, j;
	for (j = 0; j < 8; j++) {
		while (!(GPIOB->IDR & GPIO_IDR_IDR1));   	// wait for the pin to go high
		delay (40);
		if (!(GPIOB->IDR & GPIO_IDR_IDR1)) {   		// if the pin is low
			i &= ~(1 << (7 - j));   				// write 0
		}
		else i |= (1 << (7 - j));  					// if the pin is high, write 1
		while (GPIOB->IDR & GPIO_IDR_IDR1);  		// wait for the pin to go low
	}
	return i;
}

void delay(const uint32_t us) {
    uint32_t start = ticks_delay;
    while((ticks_delay - start) < us);
}

void mcu_init() 
{
	SysTick_Config(SystemCoreClock/1000000);		//1/T = f, 1/1us = 1000000
}	

void SysTick_Handler(void) {
  ticks_delay++;
}
