/**
 ​ ​*​ ​@file​ ​pwm.h
 ​ ​*​ ​@brief​ ​This file has function prototypes of implementation functions of PWM module for setting LED's
  * The LED's are Set, clear and transition from one state to other.
 ​ * It also has macros, includes, enum.
  *
 ​ * ​@author​ ​Rishikesh Goud Sundaragiri
 ​ ​*​ ​@date​ March 6 2023
 ​ ​*/

#ifndef __PWM_H__
#define __PWM_H__

#include <stdio.h>
#include "board.h"
#include "MKL25Z4.h"
#include "stdbool.h"
#include "fsl_debug_console.h"

#define IGNORE_BUTTON true
#define PERIOD 32768
#define RED_LED_PIN 18
#define BLUE_LED_PIN 1
#define GREEN_LED_PIN 19
#define STOP 1
#define GO 2
#define WARNING 3
#define WARNING_BP 4
#define CROSSWALK 5
#define ZERO 0
#define ONE 1
#define TOUCH_DETECTED 20
#define COUNT_FOR_TRANSITION 25
#define COUNT_FOR_CONSTANT 40
#define MAX_TRANSITION_ITERATIONS 16
#define GREEN_LEVEL 1285
#define BLUE_LEVEL 3855
#define INCREMENT_OR_DECREMENT_CNV 2048
#define GREEN_TRANSITION_LEVEL 1967
#define BLUE_TRANSITION_LEVEL 240
#define CROSSWALK_ITERATIONS 5
#define MULTIPLY_VALUE 25
#define DIVIDE_VALUE 10




/**
 ​ ​*​ ​@brief​ ​This function initializes the PWM module for RGB led's
 ​ ​*
 ​ ​* It contains setting and clearing of different bits of PWM registers.
  * Its called only once before the main loop starts.
  *
 ​ ​*​ ​@param​ None
 ​ ​*
 ​ ​*​ ​@return​ None
 ​ ​*/
void pwm_init();

void change_speed(int pwm_value);
#endif /* __PWM_H__ */
