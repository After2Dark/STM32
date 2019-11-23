#include "stm32f767xx.h"

int flag = 0, d = 150000;

void delay(int del)
{
  for(int a = 0; a <= del; a++);
}

void EXTI1_IRQHandler()
{
	if(flag == 0)
		flag = 1;
	else 
		flag =0;
	delay(90000);
  EXTI->PR |= EXTI_PR_PR1;
}

void init_all()
{
	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOAEN  | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PB;
	EXTI->IMR |= EXTI_IMR_MR1;
	EXTI->RTSR |= EXTI_RTSR_TR1;
	NVIC_EnableIRQ(EXTI1_IRQn);
	__enable_irq ();
}

int main()
{
	init_all();
	while(1)
	{
		if(flag == 0)
		{
			GPIOC->BSRR |= GPIO_BSRR_BS_8;
			delay(d);
			GPIOC->BSRR |= GPIO_BSRR_BR_8;
			GPIOC->BSRR |= GPIO_BSRR_BS_9;
			delay(d);
			GPIOC->BSRR |= GPIO_BSRR_BR_9;
			GPIOC->BSRR |= GPIO_BSRR_BS_10;
			delay(d);
			GPIOC->BSRR |= GPIO_BSRR_BR_10;
			GPIOC->BSRR |= GPIO_BSRR_BS_11;
			delay(d);
			GPIOC->BSRR |= GPIO_BSRR_BR_11;
		}
		else
		{
			GPIOC->BSRR |= GPIO_BSRR_BS_11;
			delay(d);
			GPIOC->BSRR |= GPIO_BSRR_BR_11;
			GPIOC->BSRR |= GPIO_BSRR_BS_10;
			delay(d);
			GPIOC->BSRR |= GPIO_BSRR_BR_10;
			GPIOC->BSRR |= GPIO_BSRR_BS_9;
			delay(d);
			GPIOC->BSRR |= GPIO_BSRR_BR_9;
			GPIOC->BSRR |= GPIO_BSRR_BS_8;
			delay(d);
			GPIOC->BSRR |= GPIO_BSRR_BR_8;
		}
	}
}
