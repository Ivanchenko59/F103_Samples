#include "main.h"
#include "i2c.h"

#define ADDRESS (0x3F << 1)

char *data = "Hello";

volatile uint32_t sys_tick = 0;

int main(void)
{	
	SysTick_Config(SystemCoreClock / 1000);
	
	//LED config
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~GPIO_CRH_CNF13;
	GPIOC->CRH |= GPIO_CRH_MODE13;
	GPIOC->ODR |= GPIO_ODR_ODR13;
	
	i2c_I2C1_GPIO_config();
	i2c_I2C1_config();
	
	while(1) {
	
		//Test Slave Address
		if(!i2c_I2C1_isSlaveAdressExist(ADDRESS, 10)) {
			GPIOC->ODR &= ~GPIO_ODR_ODR13;
		}
		else {
			GPIOC->ODR |= GPIO_ODR_ODR13;
		}
		
//		i2c_I2C1_masterTransmit(ADDRESS, (uint8_t*)data, 5, 100);
//		
//		for (uint32_t i = 0; i < 1e5; i++);
	}
}

void SysTick_Handler(void)
{
	sys_tick++;
}
