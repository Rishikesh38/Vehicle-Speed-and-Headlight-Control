/**
 ​ ​*​ ​@file​ ​touchpad.c
 ​ ​*​ ​@brief​ ​This file has implementation of touch module
 ​ ​*
 ​ ​*
 ​ * ​@author​ ​Rishikesh Goud Sundaragiri
 ​ ​*​ ​@date​ April 29 2023
  *
  * Identification​ ​of​ ​leveraged​ ​code : Reference is taken from
  * dean github repository
  *
  * Link for the repo : https://github.com/alexander-g-dean/ESF/tree/master/NXP
  *
 ​ ​*/

#include "touchpad.h"
#include "MKL25Z4.h"
#include "systick.h"
#define INPUT_TOUCH_DATA (TSI0->DATA & 0xFFFF)//Extracting the count from data register
#define TOUCH_OFFSET 670
#define ZERO 0
#define CHANNEL_10 10u

void Touch_init() {
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; //Enable the clock for TSI i.e. bit 5
	TSI0->GENCS = TSI_GENCS_MODE(0u) | //Set TSI in capacitive sensing(non-noise detection) mode
			TSI_GENCS_REFCHRG(0u) | //Reference oscillator charge and discharge current value to 500nA
			TSI_GENCS_DVOLT(0u) | //Set the oscillator's voltage rails to default
			TSI_GENCS_EXTCHRG(0u) | //Set electrode oscillator charge and discharge current value to 500nA
			TSI_GENCS_PS(0u) | //Divide Electrode Oscillator Frequency by 1
			TSI_GENCS_NSCN(31u) | //Scan the electrode 32 times
			TSI_GENCS_TSIEN_MASK | //Enable the TSI module
			TSI_GENCS_EOSF_MASK; //Set this bit to clear the end of scan flag
}

int Touch_Scan() {
	unsigned int scan = ZERO;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK;
	TSI0->DATA = TSI_DATA_TSICH(CHANNEL_10); //Select Channel 10
	TSI0->DATA |= TSI_DATA_SWTS_MASK; //Enabling software trigger to start the scan
	while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK)); //Waiting to scan the electrode 32 times
	scan = INPUT_TOUCH_DATA;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK; //Set this bit to clear the end of scan flag
	delay_in_milli_sec(1); //workaround to avoid getting blocked in while loop
	return scan-TOUCH_OFFSET;
}
