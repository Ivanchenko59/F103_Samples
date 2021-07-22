#include "utils.h"

volatile uint32_t ticks_delay = 0;

void clocking_init(void) 
{
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;		//clocking PORT A
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;		//clocking PORT B	
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;		//clocking PORT C	
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
}

void delay(const uint32_t milliseconds) 
{
  uint32_t start = ticks_delay;
  while((ticks_delay - start) < milliseconds);
}	

