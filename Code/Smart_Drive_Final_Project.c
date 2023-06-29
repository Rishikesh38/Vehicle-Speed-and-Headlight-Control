/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    Smart_Drive_Final_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "command_parser.h"
#include "headlights.h"
#include "ldr.h"
#include "pwm.h"
#include "sysclock.h"
#include "test.h"
#include "touchpad.h"
#include "uart.h"
#include"systick.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {
	sysclock_init();
	uart0_init();
	queue_init();
	adc_init();
	headlight_init();
	Touch_init();
	Init_Systick();
//	testing_queue();
//	test_process_command();
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif
	pwm_init();
	char c = '\0';
	char backspace_string[] = "\b \b";
	char input[1024];
	uint16_t index = 0;
	testing_queue();
	test_process_command();
	printf("\n\n\rWelcome to Smart Drive Final Project!\n\n\r");
	printf("---> ");
	while (1) {
		c = getchar();
		if (c != 33) {
			if (c == '\b' || c == '\177') {
				printf("%s", backspace_string);
				index--;
			} else {
				printf("%c", c);
				if (!(c == '\n' || c == '\r')) {
					input[index] = c;
					index++;
				} else {
					input[index] = '\0';
					printf("\n\r");
					if (process_command(input) == 0) {
						printf("\n\rUnknown command: %s\n\r", input);
					}
					index = 0;
					printf("\n\r");
					printf("---> ");
				}
			}
		} else {
			change_speed(get_speed_level());
			if (get_headlight_control()) {
				if (Touch_Scan() > 5000) {
					turn_on_headlight();
				} else if (Touch_Scan() > 700 && Touch_Scan() <= 3000) {
					turn_off_headlight();
				}

			} else {
				if (read_ldr() <= 20000) {
					turn_off_headlight();
				} else {
					turn_on_headlight();
				}
			}
		}
	}

//    /* Force the counter to be placed into memory. */
//    volatile static int i = 0 ;
//    /* Enter an infinite loop, just incrementing a counter. */
//    while(1) {
//        i++ ;
//        /* 'Dummy' NOP to allow source level single stepping of
//            tight while() loop */
//        __asm volatile ("nop");
//    }
	return 0;
}
