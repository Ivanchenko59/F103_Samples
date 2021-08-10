#include "main.h"
#include "uart.h"

volatile uint32_t sys_tick = 0;

int main(void)
{
	SysTick_Config(SystemCoreClock / 1000);
	UART1_GPIO_init();
	UART1_init();
	
	uint8_t rx_buf[10];
	
	while (1) {
	
		if (UART1_receive(rx_buf, 5, 1000)) {
			UART1_transmit(rx_buf, 5, 1000);
		}
		
	}
}

void SysTick_Handler(void)
{
	sys_tick++;
}
