/**
 ​ ​*​ ​@file​ ​uart.h
 ​ ​*​ ​@brief​ ​This file is the header file for uart module
  * It contains function prototypes, macros and includes for uart module
 ​ *
 ​ * ​@author​ ​Rishikesh Goud Sundaragiri
 ​ ​*​ ​@date​ April 1 2023
 ​ ​*/



#ifndef __UART_H__
#define __UART_H__

#include "sysclock.h"
#include "MKL25Z4.h"

#define MAX_QUEUE_SIZE 256


struct node {
	uint8_t byte;
	struct node *next;
};

struct linked_list {
	struct node *head;
	struct node *tail;
	struct node *lastnode;
	uint16_t count;
};


/**
 ​ ​*​ ​@brief​ ​This function initializes the uart module for serial communication
 ​ ​*
 ​ ​* It contains setting and clearing of different bits of uart registers.
  * Its called only once before the main loop starts.
  *
 ​ ​*​ ​@param​ None
 ​ ​*
 ​ ​*​ ​@return​ None
 ​ ​*/
void uart0_init();

/**
 ​ ​*​ ​@brief​ ​This function initializes the receive and transmit queue
 ​ ​* The transmit and receive queue are initialized to 256 bytes
  *
  *
 ​ ​*​ ​@param​ None
 ​ ​*
 ​ ​*​ ​@return​ None
 ​ ​*/
void queue_init();

/**
 ​ ​*​ ​@brief​ This function enqueues a byte into a linked list queue data structure
 ​ ​*
  *
 ​ ​*​ ​@param​ struct linked_list *queue either an receive or transmit queue, uint8_t byte is the data to enqueue
 ​ ​*
 ​ ​*​ ​@return​ returning 1 if successful and 0 if the queue is already at maximum capacity.
 ​ ​*/
uint8_t enqueue(struct linked_list *queue, uint8_t byte);

/**
 ​ ​*​ ​@brief​ This function dequeues a byte from a linked list queue. The dequeued node is added to the end of the queue.
 ​ ​*
  *
 ​ ​*​ ​@param​ struct linked_list *queue either an receive or transmit queue
 ​ ​*
 ​ ​*​ ​@return​ returning the dequeued byte if successful and 0 if the queue is empty.
 ​ ​*/
uint8_t dequeue(struct linked_list *queue);

#endif /* __UART_H__ */
