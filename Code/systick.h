/**
 ​ ​*​ ​@file​ ​systick.h
 ​ ​*​ ​@brief​ ​This file has declaration of systick module
 ​ ​* It has macros and headers of systick module
 ​ * ​@author​ ​Rishikesh Goud Sundaragiri
 ​ ​*​ ​@date​ March 6 2023
  *
  *
 ​ ​*/

#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include <stdio.h>
#include "MKL25Z4.h"
#include "core_cm0plus.h"
#define LOAD_VALUE 7499

/**
 ​ ​*​ ​@brief​ ​This function is the initialize function for systick module
 *
 ​ * ​It contains setting and clearing of different bits of systick registers.
 * Its called only once before the main loop starts.
 *
 ​ ​*​ ​@param​ None
 ​ ​*
 ​ ​*​ ​@return​ None
 ​ ​*/
void Init_Systick();

/**
 ​ ​*​ ​@brief​ ​This function is used to provide the delay in milliseconds
  * The function will provide 2.5millisec delay when you pass 1 as argument
  * So if you need 250 milliseconds delay then call it with 100 i.e. 2.5msec*100=250msec
 ​ *
 ​ ​*​ ​@param​ msec is the parameter that you use when you need delay in 2.5 times millisec
 ​ ​*
 ​ ​*​ ​@return​ None
 ​ ​*/
void delay_in_milli_sec(int msec);

/**
 ​ ​*​ ​@brief​ ​This function is used to return time in millisec since startup
 ​ *
  * If it returns 1 then its 2.5millisecs. So we can calculate time respective to return value. As we cannot return float value
  * we just return millisecs here and microsecs are handled in next function
 ​ ​*​ ​@param​ none
 ​ ​*
 ​ ​*​ ​@return​ uint32_t time since startup in millisec
 ​ ​*/
uint32_t get_now_time_in_millisec();

#endif /* __SYSTICK_H__ */
