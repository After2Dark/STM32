#include "stm32f767xx.h"

int value_to_show = 0;
int value_to_running_string = 0;
int show_mode = 0;
int counter = 0;
int value_digit = 1;
int flag = 0;
int start_digit = 1;

void init_all()
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOGEN;
	GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0;
	GPIOC->OTYPER |= GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9 | GPIO_OTYPER_OT_10 | GPIO_OTYPER_OT_11 | GPIO_OTYPER_OT_12;
	GPIOD->MODER |= GPIO_MODER_MODER2_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;
	GPIOD->OTYPER |= GPIO_OTYPER_OT_2 | GPIO_OTYPER_OT_4 | GPIO_OTYPER_OT_5 | GPIO_OTYPER_OT_6 | GPIO_OTYPER_OT_7;
	GPIOG->MODER |= GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0;
	GPIOG->OTYPER |= GPIO_OTYPER_OT_2 | GPIO_OTYPER_OT_3;
	SysTick_Config(160000);
}

int abs(int value)
{
	if(value < 0)
	{
		value = -value;
		return value;
	}
	return value;
}

int degree(int value)
{
	int rezult = 1;
	for(int i = 0; i < value; ++i)
		rezult *= 10;
	return rezult;
}

void clear_display()
{
	GPIOC->BSRR |= GPIO_BSRR_BS_8 | GPIO_BSRR_BS_9 | GPIO_BSRR_BS_10 | GPIO_BSRR_BS_11 | GPIO_BSRR_BS_12;
	GPIOD->BSRR |= GPIO_BSRR_BS_2 | GPIO_BSRR_BS_4 | GPIO_BSRR_BS_5 | GPIO_BSRR_BS_6 | GPIO_BSRR_BS_7;
	GPIOG->BSRR |= GPIO_BSRR_BS_2 | GPIO_BSRR_BS_3;
}

void display_numeric(int numeric)
{
	if(numeric < 10 && numeric >= 0)
	{
		switch(numeric)
		{
			case 0:
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_12;
				GPIOD->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_6 | GPIO_BSRR_BR_7;
				GPIOG->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_3;
				break;
			}
			case 1:
			{
				GPIOD->BSRR |= GPIO_BSRR_BR_2;
				GPIOG->BSRR |= GPIO_BSRR_BR_2;
				break;
			}
			case 2:
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_12;
				GPIOD->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_5 | GPIO_BSRR_BR_7;
				GPIOG->BSRR |= GPIO_BSRR_BR_3;
				break;
			}
			case 3:
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_12;
				GPIOD->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_5;
				GPIOG->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_3;
				break;
			}
			case 4:
			{
				GPIOD->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_5 | GPIO_BSRR_BR_6;
				GPIOG->BSRR |= GPIO_BSRR_BR_2;
				break;
			}
			case 5:
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_12;
				GPIOD->BSRR |= GPIO_BSRR_BR_5 | GPIO_BSRR_BR_6;
				GPIOG->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_3;
				break;
			}
			case 6:
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_12;
				GPIOD->BSRR |= GPIO_BSRR_BR_5 | GPIO_BSRR_BR_6 | GPIO_BSRR_BR_7;
				GPIOG->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_3;
				break;
			}
			case 7:
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_12;
				GPIOD->BSRR |= GPIO_BSRR_BR_2;
				GPIOG->BSRR |= GPIO_BSRR_BR_2;
				break;
			}
			case 8:
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_12;
				GPIOD->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_5 | GPIO_BSRR_BR_6 | GPIO_BSRR_BR_7;
				GPIOG->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_3;
				break;
			}
			case 9:
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_12;
				GPIOD->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_5 | GPIO_BSRR_BR_6;
				GPIOG->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_3;
				break;
			}
		}
	}
	else
		for(int i = 0; i <= 200000; i++)
		{
			GPIOC->BSRR |= GPIO_BSRR_BR_11;
			GPIOC->BSRR |= GPIO_BSRR_BR_12;
			GPIOD->BSRR |= GPIO_BSRR_BR_5;
			GPIOD->BSRR |= GPIO_BSRR_BR_6;
			GPIOD->BSRR |= GPIO_BSRR_BR_7;
			GPIOG->BSRR |= GPIO_BSRR_BR_3;
			clear_display();
			GPIOC->BSRR |= GPIO_BSRR_BR_10;
			GPIOD->BSRR |= GPIO_BSRR_BR_5;
			GPIOD->BSRR |= GPIO_BSRR_BR_7;
			clear_display();
			GPIOC->BSRR |= GPIO_BSRR_BR_9;
			GPIOD->BSRR |= GPIO_BSRR_BR_5;
			GPIOD->BSRR |= GPIO_BSRR_BR_7;
			clear_display();
			GPIOC->BSRR |= GPIO_BSRR_BR_8;
			GPIOD->BSRR |= GPIO_BSRR_BR_2;
			GPIOG->BSRR |= GPIO_BSRR_BR_2;
			clear_display();
		}
}

void change_value(int value,int digit, int mode)
{
	value_to_show = value;
	value_to_running_string = value;
	value_digit = degree(digit - 1);
	start_digit = degree(digit - 1);
	show_mode = mode;
}

void show_value(int value)
{
	if((value < 10000 && value > -1000) || show_mode >= 2)
	{
		for(int i = 0; i <= 100; ++i)
		{
			if(value > 0)
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_8;
				display_numeric(value%10);
				clear_display();
				if((value/10)%10 != 0 || (value/100)%10 != 0 || (value/1000)%10 != 0)
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_9;
					display_numeric((value/10)%10);
					clear_display();
				}
				if((value/100)%10 != 0 || (value/1000)%10 != 0)
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_10;
					display_numeric((value/100)%10);
					clear_display();
				}
				if((value/1000)%10 != 0)
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_11;
					display_numeric((value/1000)%10);
					clear_display();
				}
			}
			if(value == 0)
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_8;
				display_numeric(0);
				clear_display();
			}
			if(value < 0)
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_8;
				display_numeric(abs(value)%10);
				clear_display();
				if((abs(value)/10)%10 != 0 || (abs(value)/100)%10 != 0)
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_9;
					display_numeric((abs(value)/10)%10);
					clear_display();
				}
				else
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_9;
					GPIOD->BSRR |= GPIO_BSRR_BR_5;
					clear_display();
				}
				if((abs(value)/100)%10 != 0)
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_10;
					display_numeric((abs(value)/100)%10);
					clear_display();
				}
				else
				{
					if((abs(value)/10)%10 != 0)
					{
						GPIOC->BSRR |= GPIO_BSRR_BR_10;
						GPIOD->BSRR |= GPIO_BSRR_BR_5;
						clear_display();
					}
				}
				if((abs(value)/100)%10 != 0)
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_11;
					GPIOD->BSRR |= GPIO_BSRR_BR_5;
					clear_display();
				}
			}
		}
	}
	else
		for(int i = 0; i <= 100; i++)
		{
			GPIOC->BSRR |= GPIO_BSRR_BR_11;
			GPIOC->BSRR |= GPIO_BSRR_BR_12;
			GPIOD->BSRR |= GPIO_BSRR_BR_5;
			GPIOD->BSRR |= GPIO_BSRR_BR_6;
			GPIOD->BSRR |= GPIO_BSRR_BR_7;
			GPIOG->BSRR |= GPIO_BSRR_BR_3;
			clear_display();
			GPIOC->BSRR |= GPIO_BSRR_BR_10;
			GPIOD->BSRR |= GPIO_BSRR_BR_5;
			GPIOD->BSRR |= GPIO_BSRR_BR_7;
			clear_display();
			GPIOC->BSRR |= GPIO_BSRR_BR_9;
			GPIOD->BSRR |= GPIO_BSRR_BR_5;
			GPIOD->BSRR |= GPIO_BSRR_BR_7;
			clear_display();
			GPIOC->BSRR |= GPIO_BSRR_BR_8;
			GPIOC->BSRR |= GPIO_BSRR_BR_12;
			GPIOD->BSRR |= GPIO_BSRR_BR_2 | GPIO_BSRR_BR_5 | GPIO_BSRR_BR_7;
			GPIOG->BSRR |= GPIO_BSRR_BR_3;
			clear_display();
		}
}

void running_string(int value)
{
	if(flag == 0)
	{
		for(int i = 0; i <= 100; ++i)
		{
			if(value > 0)
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_8;
				display_numeric(value%10);
				clear_display();
				if((value/10)%10 != 0 || (value/100)%10 != 0 || (value/1000)%10 != 0 || start_digit/value_digit >= degree(1))
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_9;
					display_numeric((value/10)%10);
					clear_display();
				}
				if((value/100)%10 != 0 || (value/1000)%10 != 0 || start_digit/value_digit >= degree(2))
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_10;
					display_numeric((value/100)%10);
					clear_display();
				}
				if((value/1000)%10 != 0 || start_digit/value_digit >= degree(3))
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_11;
					display_numeric((value/1000)%10);
					clear_display();
				}
			}
			if(value == 0)
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_8;
				display_numeric(0);
				clear_display();
			}
			if(value < 0)
			{
				GPIOC->BSRR |= GPIO_BSRR_BR_8;
				display_numeric(abs(value)%10);
				clear_display();
				if(start_digit/value_digit >= degree(1))
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_9;
					display_numeric((abs(value)/10)%10);
					clear_display();
				}
				if(start_digit/value_digit >= degree(2))
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_10;
					display_numeric((abs(value)/100)%10);
					clear_display();
				}
				if(start_digit/value_digit >= degree(3))
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_11;
					display_numeric((abs(value)/1000)%10);
					clear_display();
				}
				if(start_digit/value_digit == degree(0))
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_9;
					GPIOD->BSRR |= GPIO_BSRR_BR_5;
					clear_display();
				}
				if(start_digit/value_digit == degree(1))
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_10;
					GPIOD->BSRR |= GPIO_BSRR_BR_5;
					clear_display();
				}
				if(start_digit/value_digit == degree(2))
				{
					GPIOC->BSRR |= GPIO_BSRR_BR_11;
					GPIOD->BSRR |= GPIO_BSRR_BR_5;
					clear_display();
				}
			}
		}
	}
	if(flag <= 300 / show_mode && flag != 0)
	{
		for(int i = 0; i <= 100; ++i)
		{
			GPIOC->BSRR |= GPIO_BSRR_BR_8;
			display_numeric(abs(value)%10);
			clear_display();
			GPIOC->BSRR |= GPIO_BSRR_BR_9;
			display_numeric((abs(value)/10)%10);
			clear_display();
			GPIOC->BSRR |= GPIO_BSRR_BR_10;
			display_numeric((abs(value)/100)%10);
			clear_display();
			GPIOC->BSRR |= GPIO_BSRR_BR_11;
			display_numeric((abs(value)/1000)%10);
			clear_display();
		}
		++flag;
	}
	if((flag <= 600 / show_mode && flag > 300 / show_mode) && flag != 0)
	{
		for(int i = 0; i <= 100; ++i)
		{
			GPIOC->BSRR |= GPIO_BSRR_BR_9;
			display_numeric(abs(value)%10);
			clear_display();
			GPIOC->BSRR |= GPIO_BSRR_BR_10;
			display_numeric((abs(value)/10)%10);
			clear_display();
			GPIOC->BSRR |= GPIO_BSRR_BR_11;
			display_numeric((abs(value)/100)%10);
			clear_display();
		}
			++flag;
	}
	if((flag <= 900 / show_mode && flag > 600 / show_mode) && flag != 0)
	{
		for(int i = 0; i <= 100; ++i)
		{
			GPIOC->BSRR |= GPIO_BSRR_BR_10;
			display_numeric(abs(value)%10);
			clear_display();
			GPIOC->BSRR |= GPIO_BSRR_BR_11;
			display_numeric((abs(value)/10)%10);
			clear_display();
		}
		++flag;
	}
	if((flag <= 1200 / show_mode && flag > 900 / show_mode) && flag != 0)
	{
		for(int i = 0; i <= 100; ++i)
		{
			GPIOC->BSRR |= GPIO_BSRR_BR_11;
			display_numeric(abs(value)%10);
			clear_display();
		}
		++flag;
	}
	if(flag >= 1200 / show_mode && flag != 0)
	{
		clear_display();
		show_mode = 0;
		flag = 0;
	}
}

void SysTick_Handler(void)
{
	clear_display();
	if(show_mode == 1)
		show_value(value_to_show);
	if(show_mode >= 2 && show_mode <= 10)
	{
		++counter;
		if(counter >= 300 / show_mode)
		{
			if(value_digit != 1)
				value_digit /= 10;
			counter = 0;
		}
		running_string((int)value_to_running_string/value_digit);
		if(value_digit == 1 && flag == 0)
			flag = 1;
	}
}
