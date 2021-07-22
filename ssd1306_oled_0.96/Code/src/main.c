#include "main.h"

int main(void) 
{
	mcu_init();
	
	while(1) 
	{
		
				
		SSD1306_GotoXY(10, 20); 
		SSD1306_Puts("Hello", &Font_16x26, SSD1306_COLOR_WHITE); 
		SSD1306_DrawCircle(60, 55, 7, SSD1306_COLOR_WHITE); 
		
		SSD1306_UpdateScreen();
		SSD1306_Fill(SSD1306_COLOR_BLACK);
		
	
	}
}

void mcu_init() 
{
	SysTick_Config(SystemCoreClock/1000);
	
	clocking_init();
	SSD1306_Init();
}	

void SysTick_Handler() 
{
	ticks_delay++;
}
