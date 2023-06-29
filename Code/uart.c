/**
 ​ ​*​ ​@file​ ​uart.c
 ​ ​*​ ​@brief​ ​This file has implementation of Uart module for serial communication
  *
 ​ *
  * Identification​ ​of​ ​leveraged​ ​code : Reference for uart init function is taken from
  * dean github repository.
  *
  * Link for the repo : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/UART.c
  *
 ​ * ​@author​ ​Rishikesh Goud Sundaragiri
 ​ ​*​ ​@date​ April 1 2023
 ​ ​*/



#include "uart.h"
#include <stdlib.h>
#include "string.h"

#define UART_OVERSAMPLE_RATE (16)
#define BAUD_RATE (38400)
#define NINE_BIT_DATA 1
#define PARITY_ENABLE 1
#define EVEN_PARITY 0

struct linked_list *tx_queue = NULL;
struct linked_list *rx_queue = NULL;



void uart0_init()
{
//	uint16_t sbr;
//	// Enable clock gating for PORTA
//	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
//
//	// Set pins to UART0 Rx and Tx
//	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
//	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
//
//	// Enable clock gating for UART0
//	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
//
//	// Make sure transmitter and receiver are disabled before init
//	UART0->C2 &= (~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK);
//
//	// Set UART clock to 48 MHz clock
//	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
//	SIM->SOPT2 &= ~(SIM_SOPT2_PLLFLLSEL_MASK);
//
//	// Set baud rate and oversampling ratio
//	sbr = (uint16_t)((SYSCLOCK_FREQUENCY) / ((UART_OVERSAMPLE_RATE) * 38400));
//	UART0->BDH &= ~UART0_BDH_SBR_MASK;
//	UART0->BDH |= UART0_BDH_SBR(sbr >> 8);
//	UART0->BDL = UART0_BDL_SBR(sbr);
//	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE - 1);
//
//	//Use 9 data bit mode, use even parity
//	UART0->C1 |= UART0_C1_M(NINE_BIT_DATA) | UART0_C1_PE(PARITY_ENABLE) | UART0_C1_PT(EVEN_PARITY);
//	UART0->BDH |= UART0_BDH_SBNS(0);
//
//	// Clear error flags
//	UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
//					UART0_S1_FE_MASK | UART0_S1_PF_MASK;
//
//	// Enable receive interrupts but not transmit interrupts yet
//	UART0->C2 |= UART_C2_RIE(1);
//
//	// Enable UART receiver and transmitter
//	UART0->C2 |= (UART0_C2_RE(1) | UART0_C2_TE(1));
//	NVIC_SetPriority(UART0_IRQn, 0);
//	NVIC_ClearPendingIRQ(UART0_IRQn);
//	NVIC_EnableIRQ(UART0_IRQn);
	uint16_t sbr;
	uint32_t baud_rate = 115200;
	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to 48 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	sbr = (uint16_t)((24e6)/(baud_rate * 16));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(16-1);

	// select one stop bit
	UART0->BDH |=  UART0_BDH_SBNS(0);

	// Don't enable loopback mode, use 8 data bit mode, disable 0
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0);
	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
			| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Try it a different way
	UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
									UART0_S1_FE_MASK | UART0_S1_PF_MASK;

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	// Interrupts

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	UART0->S1 &= ~UART0_S1_RDRF_MASK;

	NVIC_SetPriority(UART0_IRQn, 0);
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

}



void UART0_IRQHandler(void)
{
	uint8_t byte_data = 0;
	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK))
	{
		// clear the error flags
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK;
	}

	if (UART0->S1 & UART0_S1_RDRF_MASK)
	{
		// received a character
		byte_data = UART0->D;
		enqueue(rx_queue, byte_data);
	}
	// transmitter interrupt enabled && tx buffer empty
	if ( (UART0->C2 & UART0_C2_TIE_MASK) && (UART0->S1 & UART0_S1_TDRE_MASK) )
	{
		if(tx_queue->head->byte != '\0')
		{
			UART0->D = dequeue(tx_queue);

		}
		else
		{
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
	}
}

void queue_init() {

	tx_queue = malloc(sizeof(struct linked_list));
	tx_queue->head = NULL;
	tx_queue->tail = NULL;
	tx_queue->count = 0;

	rx_queue = malloc(sizeof(struct linked_list));
	rx_queue->head = NULL;
	rx_queue->tail = NULL;
	rx_queue->count = 0;

	struct node *tx_buffer = malloc(sizeof(struct node) * MAX_QUEUE_SIZE);
	struct node *rx_buffer = malloc(sizeof(struct node) * MAX_QUEUE_SIZE);

	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		tx_buffer[i].byte = '\0';
		tx_buffer[i].next = (i == 255) ? NULL : &tx_buffer[i + 1];
		rx_buffer[i].byte = '\0';
		rx_buffer[i].next = (i == 255) ? NULL : &rx_buffer[i + 1];
	}

	tx_queue->head = &tx_buffer[0];
	tx_queue->lastnode = &tx_buffer[255];
	rx_queue->head = &rx_buffer[0];
	rx_queue->lastnode = &rx_buffer[255];
}


uint8_t enqueue(struct linked_list *queue, uint8_t byte) {
    if (queue->count > MAX_QUEUE_SIZE) {
        return 0;
    }
    queue->count++;
    if (queue->head->byte == '\0') {
        queue->head->byte = byte;
        queue->tail = queue->head;
    }
    else{
        queue->tail->next->byte = byte;
        queue->tail = queue->tail->next;
    }
    return 1;
}

uint8_t dequeue(struct linked_list *queue) {
    if (queue->count <= 0) {
        return 0;
    }
    struct node *node_to_dequeue = queue->head;
    uint8_t byte = node_to_dequeue->byte;
    queue->head = node_to_dequeue->next;
    node_to_dequeue->byte = '\0';
    node_to_dequeue->next = NULL;
    queue->lastnode->next = node_to_dequeue;
    queue->lastnode = queue->lastnode->next;
    queue->count--;
    return byte;
}

int __sys_write(int handle, char *buf, int size)
{
	int i = 0;
	while((MAX_QUEUE_SIZE - tx_queue->count) < size);
	while((buf[i] != '\0'))
	{
		enqueue(tx_queue, buf[i]);
		i++;
	}
	UART0->C2 |= UART_C2_TIE(1); //Enable Transmit interrupt
	return 0;
}

//int __sys_readc(void)
//{
//	//wait here until a char is received in the receive buffer
//	//take the first byte from the receive queue and return it
//	int return_value = 0;
//	while(rx_queue->head->byte == '\0');
//	return_value = dequeue(rx_queue);
//	return return_value;
//}

int __sys_readc(void)
{
	//wait here until a char is received in the receive buffer
	//take the first byte from the receive queue and return it
	int return_value = 0;
	//while(rx_queue->head->byte == '\0');
	if(rx_queue->count > 0 ){
		return_value = dequeue(rx_queue);
		return return_value;
	}
	else{
		return 33;
	}

}

