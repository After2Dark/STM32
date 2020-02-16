#ifndef _indicator_h
#define _indicator_h

void init_all();

void clear_display();

void display_numeric(int numeric);

void change_value(int value,int mode);

void SysTick_Handler(void);

#endif
