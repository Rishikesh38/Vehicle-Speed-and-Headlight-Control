/**
 ​ ​*​ ​@file​ ​command_parser.c
 ​ ​*​ ​@brief​ ​This file has implementation of command parser module for serial communication
  *
 ​ *
  * Identification​ ​of​ ​leveraged​ ​code : Reference for this is taken from Prof. lecture PPT
  *
 ​ * ​@author​ ​Rishikesh Goud Sundaragiri
 ​ ​*​ ​@date​ April 1 2023
 ​ ​*/


#include "command_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 1024

static int set_pwm_level = 0;
static bool manual_mode = false;
typedef void (*command_handler_t)(int, char *argv[]);

typedef struct {
    const char *name;
    command_handler_t handler;
} command_table_t;



static const command_table_t commands[] = {
    {"Eco", EcoFunction},
    {"Normal", NormalFunction},
    {"Sport", SportFunction},
	{"Track", TrackFunction},
	{"ManualOn", ManualOnFunction},
	{"ManualOff", ManualOffFunction},
	{"Help", HelpFunction}
};

static const int num_commands = sizeof(commands) / sizeof(command_table_t);

int checkCommand(int argc, char *argv[]){
    for (int i=0; i < num_commands; i++) {
        if (strcasecmp(argv[0], commands[i].name) == 0) {
            commands[i].handler(argc, argv);
            return 1;
        }
    }
    return 0;
}

int process_command(char* input){
    char *argv[SIZE];
    int argc = 0;
    memset(argv, 0, sizeof(argv));

    char* p = strtok(input, " ");

    while (p != NULL)
    {
    	argv[argc++] = p;
        p = strtok(NULL, " ");
    }
    return checkCommand(argc,argv);
}

void HelpFunction()
{
	printf("\n\n\rInfo about all the supported commands : \n\r");
	printf("\n\rEco : This mode is specifically designed to enhance fuel efficiency, which typically involves constraining the vehicle's speed to 0.55 times of its maximum speed.\n\r");
	printf("\n\rNormal :  This is the default mode that provides a balanced level of performance and fuel efficiency, where the vehicle's speed is approximately 0.7 times of its maximum.\n\r");
	printf("\n\rSport : This mode is aimed at more dynamic and responsive driving and allows for higher speeds, up to 0.85 times of the vehicle's maximum speed.\n\r");
	printf("\n\rTrack : This mode is optimized for high-performance driving on a race track and allowing for even more aggressive acceleration, where the vehicle  operates 0.95 times maximum speed.\n\r");
	printf("\n\rManualOn : Enabling the automatic head lights function will activate the head lights that are managed by an LDR sensor, causing them to turn on or off depending on the surrounding \n\r\t   light conditions.\n\r");
	printf("\n\rManualOff : This will turn off the automatic head lights feature and head lights can be controlled manually by touch pad.\n\r");
}

void EcoFunction()
{
	set_pwm_level = 32768 - (32768*0.55); //55% of maximum speed
}

void NormalFunction()
{
	set_pwm_level = 32768 - (32768*0.70); //70% of the maximum speed
}

void SportFunction()
{
	set_pwm_level = 32768 - (32768*0.85); //85% of the maximum speed
}

void TrackFunction()
{
	set_pwm_level = 32768 - (32768*0.95); //95% of the maximum speed
}

 void ManualOnFunction()
{
	manual_mode = true;
}

 void ManualOffFunction()
 {
	 manual_mode = false;
 }

 int get_speed_level()
 {
	 return set_pwm_level;
 }

 bool get_headlight_control()
 {
	 return manual_mode;
 }
