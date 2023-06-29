/**
 ​ ​*​ ​@file​ ​touchpad.h
 ​ ​*​ ​@brief​ ​This is the header file for implementation of touch module
 ​ ​*
 ​ ​* It has the function declarations, includes and macros
 ​ * ​@author​ ​Rishikesh Goud Sundaragiri
 ​ ​*​ ​@date​ April 29 2023
  *
 ​ ​*/

#ifndef __TOUCH_PAD_H__
#define __TOUCH_PAD_H__




/**
 ​ ​*​ ​@brief​ ​This function Initializes the Touch module
 ​ ​*
 ​ ​* The Clock and GPIO register bits are set to initialize TSI module
 ​ ​*​ ​@param​ None
 ​ ​*
 ​ ​*​ ​@return​ None
 ​ ​*/
void Touch_init();

/**
 ​ ​*​ ​@brief​ ​This function scans the Touch slider
 ​ ​*
 ​ ​* The TSI register bits are set to initialize read data from touch slider
 ​ ​*​ ​@param​ None
 ​ ​*
 ​ ​*​ ​@return​ It returns an integer which is equal to (scan - TOUCH_OFFSET)
 ​ ​*/
int Touch_Scan();

#endif /* __TOUCH_PAD_H__ */
