/**
 ​ ​*​ ​@file​ ​command_parser.h
 ​ ​*​ ​@brief​ ​This file is the header file for command parser module
  *
  *
 ​ * ​@author​ ​Rishikesh Goud Sundaragiri
 ​ ​*​ ​@date​ April 1 2023
 ​ ​*/


#ifndef __COMMAND_PARSER__
#define __COMMAND_PARSER__

#include <stdbool.h>

/**
 ​ ​*​ ​@brief​ This function checks if a command specified in the argument vector matches one of the registered commands
  * if so, executes the corresponding command handler function.
 ​ ​*
  *
 ​ ​*​ ​@param​ int argc is the count of arguments and char *argv[] will have the arguments
 ​ ​*
 ​ ​*​ ​@return​ If no matching command is found, it returns 0. Else it returns 1
 ​ ​*/
int checkCommand(int argc, char *argv[]);

/**
 ​ ​*​ ​@brief​ This function processes a command input string by tokenizing it into arguments.
  * And calling the checkCommand function to check if a matching command exists.
 ​ ​*
  *
 ​ ​*​ ​@param​ char* input is the user input
 ​ ​*
 ​ ​*​ ​@return​ If no matching command is found, it returns 0. Else it returns 1
 ​ ​*/
int process_command(char* input);

void HelpFunction();
void EcoFunction();
void NormalFunction();
void SportFunction();
void TrackFunction();
void ManualOnFunction();
void ManualOffFunction();
int get_speed_level();
bool get_headlight_control();

#endif /* __COMMAND_PARSER__ */
