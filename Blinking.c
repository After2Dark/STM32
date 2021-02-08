#include "stm32f767xx.h"

int d = 500000;

void delay(int del)
{
  for(int a = 0; a <= del; a++)
}

void init_all(){
	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0;
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
}

int main()
{
	init_all();
	while(1)
	{
		delay(5*d);
		GPIOC->BSRR |= GPIO_BSRR_BS_8;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BR_8;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BS_8;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BR_8;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BS_8;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BR_8;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BS_8;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BR_8;
		delay(d);
		
		GPIOC->BSRR |= GPIO_BSRR_BS_9;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BR_9;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BS_9;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BR_9;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BS_9;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BR_9;
		delay(d);
		
		GPIOC->BSRR |= GPIO_BSRR_BS_10;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BR_10;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BS_10;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BR_10;
		delay(d);
		
		GPIOC->BSRR |= GPIO_BSRR_BS_11;
		delay(d);
		GPIOC->BSRR |= GPIO_BSRR_BR_11;
		delay(d);
		
		delay(5*d);
	}
}
