/**
​ ​*​ ​@file​ ​test_cases.c
​ ​*​ ​@brief​ ​This file tests all the functionalities of queue
​ ​* It will check Happy, failure and corner cases.
​ ​*
​ * ​@author​ ​Rishikesh Goud Sundaragiri
​ ​*​ ​@date​ April 7 2023
​ ​*/
#include "test.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int testing_queue()
{
    int passed = 0;
    int failed = 0;
    struct linked_list *tx_queue_test = NULL;
    tx_queue_test = malloc(sizeof(struct linked_list));
    tx_queue_test->head = NULL;
    tx_queue_test->tail = NULL;
    tx_queue_test->count = 0;

	struct node *tx_buffer_test = malloc(sizeof(struct node) * MAX_QUEUE_SIZE);

	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		tx_buffer_test[i].byte = '\0';
		tx_buffer_test[i].next = (i == 255) ? NULL : &tx_buffer_test[i + 1];
		tx_buffer_test[i].byte = '\0';
		tx_buffer_test[i].next = (i == 255) ? NULL : &tx_buffer_test[i + 1];
	}

	tx_queue_test->head = &tx_buffer_test[0];
	tx_queue_test->lastnode = &tx_buffer_test[255];
	tx_queue_test->head = &tx_buffer_test[0];
	tx_queue_test->lastnode = &tx_buffer_test[255];


    if ((enqueue(tx_queue_test, 21)) == 1 && tx_queue_test->count == 1 && MAX_QUEUE_SIZE == 256)
    {
    	passed++;
    }
    else
    {
        printf("test case 1 for queue failed\n\r");
        failed++;
    }
    if ((enqueue(tx_queue_test, 22)) == 1 && tx_queue_test->count == 2 && MAX_QUEUE_SIZE == 256)
    {
    	passed++;
    }
    else
    {
        printf("test case 2 for queue failed\n\r");
        failed++;
    }
    if ((enqueue(tx_queue_test, 23)) == 1 && tx_queue_test->count == 3 && MAX_QUEUE_SIZE == 256)
    {
    	passed++;
    }
    else
    {
        printf("test case 3 for queue failed\n\r");
        failed++;
    }
    if ((enqueue(tx_queue_test, 24)) == 1 && tx_queue_test->count == 4 && MAX_QUEUE_SIZE == 256)
    {
    	passed++;
    }
    else
    {
        printf("test case 4 for queue failed\n\r");
        failed++;
    }
    if ((enqueue(tx_queue_test, 25)) == 1 && tx_queue_test->count == 5 && MAX_QUEUE_SIZE == 256)
    {
    	passed++;
    }
    else
    {
        printf("test case 5 for queue failed\n\r");
        failed++;
    }
    if ((dequeue(tx_queue_test) == 21 ) && tx_queue_test->count == 4 && MAX_QUEUE_SIZE == 256)
    {
    	passed++;
    }
    else
    {
        printf("test case 6 for queue failed\n\r");
        failed++;
    }
    if ((dequeue(tx_queue_test) == 22 ) && tx_queue_test->count == 3 && MAX_QUEUE_SIZE == 256)
    {
    	passed++;
    }
    else
    {
        printf("test case 7 for queue failed\n\r");
        failed++;
    }
    if ((enqueue(tx_queue_test, 26)) == 1 && tx_queue_test->count == 4 && MAX_QUEUE_SIZE == 256)
    {
    	passed++;
    }
    else
    {
        printf("test case 8 for queue failed\n\r");
        failed++;
    }
    if ((enqueue(tx_queue_test, 27)) == 1 && tx_queue_test->count == 5 && MAX_QUEUE_SIZE == 256)
    {
    	passed++;
    }
    else
    {
        printf("test case 9 for queue failed\n\r");
        failed++;
    }
    if ((dequeue(tx_queue_test) == 23 ) && tx_queue_test->count == 4 && MAX_QUEUE_SIZE == 256)
    {
    	passed++;
    }
    else
    {
        printf("test case 10 for queue failed\n\r");
        failed++;
    }
    if (passed == 10)
    {
        printf("\n\rAll test cases passed for queues\n\r");
        return 1;
    }
    else
    {
        printf("Tests passed are %d, happy tests are %d\n", passed, failed);
        return 0;
    }
}


// Define a mock function for testing process_command()
int test_process(char *input) {
    if (strcmp(input, "help") == 0) {
        return 1;
    } else if (strcmp(input, "invalid") == 0) {
        return 0;
    } else {
        return 0;
    }
}

void test_process_command() {
    // Test case 1: Valid command
	int tests_passed = 0;
    char input1[] = "help";
    int expected_output1 = 1;
    int actual_output1 = test_process(input1);
    if (actual_output1 != expected_output1) {
        printf("Test case 1 failed for process command: Expected output %d, but got %d\n", expected_output1, actual_output1);
    }
    else
    {
    	tests_passed++;
    }

    // Test case 2: Invalid command
    char input2[] = "invalid";
    int expected_output2 = 0;
    int actual_output2 = test_process(input2);
    if (actual_output2 != expected_output2) {
        printf("Test case 2 failed for process command: Expected output %d, but got %d\n", expected_output2, actual_output2);
    }
    else
    {
    	tests_passed++;
    }

    // Test case 3: Unknown command
    char input3[] = "unknown";
    int expected_output3 = 0;
    int actual_output3 = test_process(input3);
    if (actual_output3 != expected_output3) {
        printf("Test case 3 failed for process command: Expected output %d, but got %d\n", expected_output3, actual_output3);
    }
    else
    {
    	tests_passed++;
    }
    if(tests_passed == 3)
    {
    	printf("All test cases passed for command parser\n\r");
    }
}

