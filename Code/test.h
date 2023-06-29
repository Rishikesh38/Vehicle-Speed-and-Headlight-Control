/**
​ ​*​ ​@file​ ​test.h
​ ​*​ ​@brief​ ​This is the header file for test functionality
​ ​*
​ ​*​ ​This​ ​header​ ​file contains preprocessor macros, headers ​and
​ ​*​ function prototypes​.
​ ​*
 * ​@author​ ​Rishikesh Goud Sundaragiri
​ ​*​ ​@date​ April 7 2023
​ ​*​ ​
​ ​*/

#ifndef __TEST_H__
#define __TEST_H__




/**
​ ​*​ ​@brief​ This function is the single test function
 * that tests the queue
 *
​ ​*
​ ​*​ ​@return​ It either return 1 if all tests succeeded, and 0 otherwise.
​ ​*/

int testing_queue();
int test_process(char *input);
void test_process_command();
#endif /*__TEST_H__ */
