#include "stm32f767xx.h"

int d = 600000, flag = 0, i = 0;

void delay(int del)
{
  for(int a = 0; a <= del; a++);
}

void EXTI1_IRQHandler()
{
	GPIOC->BSRR |= GPIO_BSRR_BS_8;
	delay(d);
	GPIOC->BSRR |= GPIO_BSRR_BR_8;
	if(i != 0)
		flag = 1;
	i++;
	delay(90000);
  EXTI->PR |= EXTI_PR_PR1;
}

void EXTI2_IRQHandler()
{
	GPIOC->BSRR |= GPIO_BSRR_BS_9;
	delay(d);
	GPIOC->BSRR |= GPIO_BSRR_BR_9;
	if(i != 1)
		flag = 1;
	i++;
	delay(90000);
  EXTI->PR |= EXTI_PR_PR2;
}

void EXTI3_IRQHandler()
{
	GPIOC->BSRR |= GPIO_BSRR_BS_10;
	delay(d);
	GPIOC->BSRR |= GPIO_BSRR_BR_10;
	if(i != 2)
		flag = 1;
	i++;
	delay(90000);
  EXTI->PR |= EXTI_PR_PR3;
}

void EXTI4_IRQHandler()
{
	GPIOC->BSRR |= GPIO_BSRR_BS_11;
	delay(d);
	GPIOC->BSRR |= GPIO_BSRR_BR_11;
	if(i != 3)
		flag = 1;
	i++;
	delay(90000);
  EXTI->PR |= EXTI_PR_PR4;
}



void init_all()
{
	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOFEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0;
	
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PB | SYSCFG_EXTICR1_EXTI2_PC | SYSCFG_EXTICR1_EXTI3_PB;
	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PF;
	EXTI->IMR |= EXTI_IMR_MR1 | EXTI_IMR_MR2 | EXTI_IMR_MR3 | EXTI_IMR_MR4;
	EXTI->RTSR |= EXTI_RTSR_TR1 | EXTI_RTSR_TR2 | EXTI_RTSR_TR3 | EXTI_RTSR_TR4;
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI4_IRQn);
	__enable_irq ();
}

int main()
{
	init_all();
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
	while(1){
		if(i == 4)
		{
			if(flag == 0)
			{
				GPIOC->BSRR |= GPIO_BSRR_BS_11;
				delay(d);
				GPIOC->BSRR |= GPIO_BSRR_BR_11;
				delay(d);
			}
			else
			{
				for(int b = 0; b <= 2; b++)
				{
					GPIOC->BSRR |= GPIO_BSRR_BS_10;
					delay(d);
					GPIOC->BSRR |= GPIO_BSRR_BR_10;
					delay(d);
				}
				GPIOC->BSRR |= GPIO_BSRR_BS_8;
				GPIOC->BSRR |= GPIO_BSRR_BS_9;
				GPIOC->BSRR |= GPIO_BSRR_BS_10;
				GPIOC->BSRR |= GPIO_BSRR_BS_11;
				delay(5*d);
				GPIOC->BSRR |= GPIO_BSRR_BR_8;
				GPIOC->BSRR |= GPIO_BSRR_BR_9;
				GPIOC->BSRR |= GPIO_BSRR_BR_10;
				GPIOC->BSRR |= GPIO_BSRR_BR_11;
				i = 0;
				flag = 0;
			}
		}
	}
}
