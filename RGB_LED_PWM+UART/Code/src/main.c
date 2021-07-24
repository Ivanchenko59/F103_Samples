#include "main.h"

#define PERIOD(F) (1e6/F)
#define FREQ 200

volatile uint32_t ticks_delay = 0;

uint8_t BLUE = 0;
uint8_t RED = 0;
uint8_t GREEN = 0;
uint8_t flag = 0;
char temp;

int main(void) 
{
	mcu_init();
	UART1_init();
	TIM4_init();	
	
	while(1) {
		if (USART1->SR & USART_SR_RXNE) 						//if RX is not empty
		{
			temp = USART1->DR;								//fetch the data received
			
			switch (flag) {
			case 1:
				RED = temp;
				TIM4->CCR3 = PERIOD(FREQ) / 57 * RED - 1;
				flag = 0;
				break;
			case 2:
				GREEN = temp;
				TIM4->CCR2 = PERIOD(FREQ) / 57 * GREEN - 1;
				flag = 0;
				break;
			case 3:
				BLUE = temp;
				TIM4->CCR4 = PERIOD(FREQ) / 57 * BLUE - 1;
				flag = 0;
				break;
			} 	
			
		}
		
		if (!flag) {
				switch (temp) {
					case 'R':
						flag = 1;
						break;
					case 'G':
						flag = 2;
						break;
					case 'B':
						flag = 3;
						break;
				}
			}
		
	}
	
}

void delay(const uint32_t milliseconds) 
{
    uint32_t start = ticks_delay;
    while((ticks_delay - start) < milliseconds);
}

void mcu_init() 
{
	SysTick_Config(SystemCoreClock/1000);
}

void UART1_init(void)
{ 
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;                       //enable USART1
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;							//clock GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;                         //enable alternative function IO clock

	//GPIOA_9 Alternate function output Push-pull for TX
	GPIOA->CRH  &= ~GPIO_CRH_CNF9;                              
	GPIOA->CRH  |= GPIO_CRH_CNF9_1;
	GPIOA->CRH  |= GPIO_CRH_MODE9_0;

	//GPIOA_10 Input with pull-up / pull-down for RX
	GPIOA->CRH  &= ~GPIO_CRH_CNF10;
	GPIOA->CRH  |= GPIO_CRH_CNF10_1;
	GPIOA->CRH  &= ~GPIO_CRH_MODE10;
	//GPIOA->BSRR |= GPIO_ODR_ODR10;
	/*-------------------------------------------------------------
	BAUD = Fclk / (16 * USARTDIV)
	USARTDIV = Fclk / (16 * BAUD)
	USARTDIV = 72000000 / (16 * 9600) = 468.75
	Mantisa 468 = 0x1D4
	Fraction 16*0.75 = 12 = 0xC
	BRR = 0x1D4C
	-------------------------------------------------------------*/
	USART1->BRR = 0x1D4C;    
	
	/*-------------------------------------------------------------
	USART_CR1_RE - receiver enable
	USART_CR1_TE - transmitter enable
	USART_CR1_UE - USART enable	(ENABLE LAST!)
	-------------------------------------------------------------*/
	USART1->CR1 |= USART_CR1_RE;
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_UE;
}


void TIM4_init(void) 
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;			//clocking GPIOB
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; 		//alt. function
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;			//clocking TIM4
	
	//GPIOB9 alt. func for TIM4 CHANNEL4
	GPIOB->CRH &= ~GPIO_CRH_CNF9;
    GPIOB->CRH |= GPIO_CRH_CNF9_1;
    GPIOB->CRH |= GPIO_CRH_MODE9;

	//GPIOB10 alt. func for TIM4 CHANNEL3
	GPIOB->CRH &= ~GPIO_CRH_CNF8;
    GPIOB->CRH |= GPIO_CRH_CNF8_1;
    GPIOB->CRH |= GPIO_CRH_MODE8;
	
	//GPIOB10 alt. func for TIM4 CHANNEL2
	GPIOB->CRL &= ~GPIO_CRL_CNF7;
    GPIOB->CRL |= GPIO_CRL_CNF7_1;
    GPIOB->CRL |= GPIO_CRL_MODE7;
	
	TIM4->CCER |= TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;	//enable channel
	TIM4->CCER |= TIM_CCER_CC2P | TIM_CCER_CC3P | TIM_CCER_CC4P;	//active low
	
	TIM4->CR1 |= TIM_CR1_ARPE;
	
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;	//PWM mode 1
	TIM4->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;	//PWM mode 1
	TIM4->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;	//PWM mode 1
	
	TIM4->CCMR2 |= TIM_CCMR2_OC4PE;						//preloader
	TIM4->CCMR2 |= TIM_CCMR2_OC3PE;						//preloader
	TIM4->CCMR1 |= TIM_CCMR1_OC2PE;						//preloader
	
	TIM4->PSC = 72 - 1;									//devide f_clk
	TIM4->ARR = PERIOD(FREQ) - 1;						//reload value
	
	TIM4->CCR3 = PERIOD(FREQ) / 9 * RED - 1;
	TIM4->CCR4 = PERIOD(FREQ) / 9 * BLUE - 1;
	TIM4->CCR2 = PERIOD(FREQ) / 9 * GREEN - 1;
	
	TIM4->EGR |= TIM_EGR_UG;
	TIM4->CR1 |= TIM_CR1_CEN;							//start timer
}

void SysTick_Handler(void) 
{
  ticks_delay++;
}
