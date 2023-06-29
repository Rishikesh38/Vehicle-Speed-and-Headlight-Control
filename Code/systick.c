/**
 ​ ​*​ ​@file​ ​systick.c
 ​ ​*​ ​@brief​ ​This file has implementation of systick module
 ​ ​* It has functions which will keep track of time in msec
 ​ ​* It helps us to provide delay in msec
 ​ * ​@author​ ​Rishikesh Goud Sundaragiri
 ​ ​*​ ​@date​ March 6 2023
  *
  *
 ​ ​*/
#include "systick.h"

static int counter = 0;
static uint32_t time = 0;
void Init_Systick(void) {
	SysTick->LOAD = (LOAD_VALUE); //this load value will divide the frequency i.e. 3mhz so we get a 2.5 msec delay
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL = 0; //it will downcount till VAL i.e. 0
	SysTick->CTRL = (SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
}

void SysTick_Handler(void) {
	counter++;
	time++;
}

void delay_in_milli_sec(int msec) {
	counter = 0;
	while (counter < msec)
		;
}

uint32_t get_now_time_in_millisec() {
	return time;
}
