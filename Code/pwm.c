/**
 ​ ​*​ ​@file​ ​pwm.c
 ​ ​*​ ​@brief​ ​This file has implementation of PWM module for setting LED's
  * The LED's are Set, clear and transition from one state to other
 ​ *
  * Identification​ ​of​ ​leveraged​ ​code : Reference for PWM init function is taken from
  * dean github repository.
  *
  * Link for the repo : https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_7/PWM_LED
  *
 ​ * ​@author​ ​Rishikesh Goud Sundaragiri
 ​ ​*​ ​@date​ March 6 2023
 ​ ​*/

#include"pwm.h"



void pwm_init() {
//	//Enable the clocks for Port D
//	//SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	//Blue FTM0_CH1, Mux Alt 4
	//Set pin to FTMs
//	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
//	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(3);
//	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
//	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(3);
	PORTD->PCR[2] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[2] |= PORT_PCR_MUX(4); //PTD 2

	// Configure TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	//SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

	//set clock source for tpm: 48 MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	//Set the MOD value for TPM0 and TPM2
	//TPM2->MOD = PERIOD - ONE;
	TPM0->MOD = PERIOD - ONE;

	//set TPM count direction to up with a divide by 2 prescaler
	TPM0->SC = TPM_SC_PS(1);
	//TPM2->SC = TPM_SC_PS(1);

	// Continue operation in debug mode
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	//TPM2->CONF |= TPM_CONF_DBGMODE(3);

	// Set channel 1 to edge-aligned low-true PWM
	TPM0->CONTROLS[2].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; //Blue
//	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; //Red
//	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; //Green

	// Set initial duty cycle
//	TPM2->CONTROLS[0].CnV = ZERO; //Red
//	TPM2->CONTROLS[1].CnV = ZERO; //Green
	TPM0->CONTROLS[2].CnV = 0; //Blue

	// Start TPM
	TPM0->SC |= TPM_SC_CMOD(1);
//	TPM2->SC |= TPM_SC_CMOD(1);
}

void change_speed(int pwm_value)
{
	TPM0->CONTROLS[2].CnV = pwm_value;
}
