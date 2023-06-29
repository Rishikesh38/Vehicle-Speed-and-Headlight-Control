#include "headlights.h"
#include "MKL25Z4.h"
#include "ldr.h"

//if less than 20000 then day or its night
#define RED_LED_PIN (18) //The pin of red led on PORTB is 18
#define BLUE_LED_PIN (1) //The pin of blue led on PORTB is 19
#define GREEN_LED_PIN (19) //The pin of green led on PORTD is 1
#define MASK(x) (1U << (x)) //Macro used to set the bits
#define GPIO_MODE 1 //Set the pin to GPIO mode

void headlight_init()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //Enable the clock of Red and Green led
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //Enable the clock of Blue led
	PTB->PDDR |= MASK(RED_LED_PIN); //Set the red led to output mode
	PTB->PDDR |= MASK(GREEN_LED_PIN); //Set the green led to output mode
	PTD->PDDR |= MASK(BLUE_LED_PIN); //Set the blue led to output mode
	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK; //Clear the bit for red led GPIO mode
	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK; //Clear the bit for green led GPIO mode
	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK; //Clear the bit for blue led GPIO mode
	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(GPIO_MODE); //Set the bit for red led to GPIO
	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(GPIO_MODE); //Set the bit for green led to GPIO
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(GPIO_MODE); //Set the bit for blue led to GPIO
	GPIOB->PSOR |= MASK(RED_LED_PIN); //Clear led bit for red led
	GPIOB->PSOR |= MASK(GREEN_LED_PIN); //Clear led bit for green led
	GPIOD->PSOR |= MASK(BLUE_LED_PIN); //Clear led bit for blue led
}

void turn_on_headlight()
{
	GPIOB->PCOR |= MASK(RED_LED_PIN); //Turn the Red led On
	GPIOB->PCOR |= MASK(GREEN_LED_PIN); //Turn the Green led On
	GPIOD->PCOR |= MASK(BLUE_LED_PIN); //Turn the Blue  On
	}

void turn_off_headlight()
{
	GPIOB->PSOR |= MASK(RED_LED_PIN); //Clear the Red led
	GPIOB->PSOR |= MASK(GREEN_LED_PIN); //Clear the Green led
	GPIOD->PSOR |= MASK(BLUE_LED_PIN); //Clear the Blue led
}
