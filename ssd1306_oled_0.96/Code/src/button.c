#include "button.h"

void init_button() {
	
	//http://easyelectronics.ru/arm-uchebnyj-kurs-vneshnie-preryvaniya.html
	AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI10_PB | AFIO_EXTICR3_EXTI11_PB ;
	AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI12_PB;
	
	GPIOB->CRH &= ~GPIO_CRH_MODE10;
	GPIOB->CRH |= GPIO_CRH_CNF10_1;
	GPIOB->CRH &= ~GPIO_CRH_CNF10_0;
	
	GPIOB->CRH &= ~GPIO_CRH_MODE11;
	GPIOB->CRH |= GPIO_CRH_CNF11_1;
	GPIOB->CRH &= ~GPIO_CRH_CNF11_0;
	
	GPIOB->CRH &= ~GPIO_CRH_MODE12;
	GPIOB->CRH |= GPIO_CRH_CNF12_1;
	GPIOB->CRH &= ~GPIO_CRH_CNF12_0;
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	EXTI->IMR  |= EXTI_IMR_MR10;
  EXTI->RTSR |= EXTI_RTSR_TR10;
  EXTI->FTSR &= ~EXTI_FTSR_TR10;
	
	EXTI->IMR  |= EXTI_IMR_MR11;
  EXTI->RTSR |= EXTI_RTSR_TR11;
  EXTI->FTSR &= ~EXTI_FTSR_TR11;
	
	EXTI->IMR  |= EXTI_IMR_MR12;
  EXTI->RTSR |= EXTI_RTSR_TR12;
  EXTI->FTSR &= ~EXTI_FTSR_TR12;
}
