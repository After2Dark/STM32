#include "stm32f767xx.h"

void USART_Init(void)
{
	RCC->AHB1ENR  	|= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR	|= RCC_APB2ENR_USART1EN;
	GPIOA->MODER	|= GPIO_MODER_MODER9_1;
	GPIOA->AFR[1]   |= GPIO_AFRH_AFRH1_0 | GPIO_AFRH_AFRH1_1 | GPIO_AFRH_AFRH1_2 ;
	USART1->CR1 	|= USART_CR1_OVER8;
	USART1->BRR 	= 0x08b;
	USART1->CR1 	|= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void Transmit_value(void *ad, int length)
{
	for(int i = length - 1; i >= 0; i--)
	{
		while ((USART1->ISR & USART_ISR_TXE)==0);
		USART1->TDR = *((char*)ad + i);
	}
}

int main(void)
{
	USART_Init();
	int value = 1;
	Transmit_value(&value, 4);
	while(1);
}
