#include "stm32f767xx.h"

uint16_t buf[9];

void Transmit_value(void *ad, int length)
{
	for(int i = length - 1; i >= 0; i--)
	{
		while ((USART1->ISR & USART_ISR_TXE)==0);
		USART1->TDR = *((char*)ad + i);
	}
	while ((USART1->ISR & USART_ISR_TXE)==0);
	USART1->TDR = 0x00;
}

void init_all()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN  | RCC_AHB1ENR_DMA2EN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN | RCC_APB2ENR_ADC1EN | RCC_APB2ENR_USART1EN;

	GPIOA->MODER |= GPIO_MODER_MODER9_1;
	GPIOA->AFR[1] |= GPIO_AFRH_AFRH1_0 | GPIO_AFRH_AFRH1_1 | GPIO_AFRH_AFRH1_2 ;
	USART1->CR1 |= USART_CR1_OVER8;
	USART1->BRR = 0x08b;
	USART1->CR1 |= USART_CR1_UE | USART_CR1_TE;

	GPIOA->MODER |= GPIO_MODER_MODER3 | GPIO_MODER_MODER4 | GPIO_MODER_MODER7;
	ADC1->SQR1 |= ADC_SQR1_L_1;
	ADC1->SQR3 |= ADC_SQR3_SQ1_0 | ADC_SQR3_SQ1_1 | ADC_SQR3_SQ2_2 | ADC_SQR3_SQ3_0  | ADC_SQR3_SQ3_1 | ADC_SQR3_SQ3_2;
	ADC1->CR1 |= ADC_CR1_SCAN;
	ADC1->CR2 |= ADC_CR2_DMA | ADC_CR2_DDS | ADC_CR2_CONT | ADC_CR2_ADON;

	DMA2_Stream0->CR &= ~DMA_SxCR_EN;
	DMA2_Stream0->CR  |= DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0 | DMA_SxCR_MINC;
	DMA2_Stream0->PAR = (uint32_t)&ADC1->DR;
	DMA2_Stream0->M0AR = (uint32_t)&buf;
	DMA2_Stream0->NDTR = 9;
   	DMA2_Stream0->CR |= DMA_SxCR_EN;
}

int main(void)
{
	init_all();
	while(1)
	{
		ADC1->CR2 |= ADC_CR2_SWSTART;
		for(int i = 0; i < 1000; i++);
		for(int i = 0; i < 9; i++)
			Transmit_value(&buf[i],2);
		for(int i = 0; i <= 1000000; ++i);
	}
}

