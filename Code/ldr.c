#include "ldr.h"
#include "MKL25Z4.h"

//#define ADC_POS (5)
#define ADC_POS (20)
static int ldr_value = 0;
//void adc_init(void)
//{
//
//	//Enable the clock
//	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
//	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
//
//	// Select analog for pin
//	PORTD->PCR[ADC_POS] &= ~PORT_PCR_MUX_MASK;
//	PORTD->PCR[ADC_POS] |= PORT_PCR_MUX(0);
//	//Set the configuration of ADC
//	ADC0->CFG1 = (ADC_CFG1_ADLPC_MASK | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE(3)
//			| ADC_CFG1_ADICLK(0));
//
//	//Set the status and control register
//	ADC0->SC1[0] = (ADC_SC1_DIFF(0) | ADC_SC1_ADCH(0b0101) |  ADC_SC1_AIEN(1));
//	ADC0->SC2 = (ADC_SC2_REFSEL(0));
//	NVIC_EnableIRQ(ADC0_IRQn);
//	//Select the system options to ADC trigger enable
//	//SIM->SOPT7 = (SIM_SOPT7_ADC0TRGSEL(9) | SIM_SOPT7_ADC0ALTTRGEN(1));
//}
//
//void ADC0_IRQHandler()
//{
//	if(ADC0->SC1[0] & ADC_SC1_COCO_MASK)
//	{
//		ldr_value = ADC0->R[0];
//	}
//}

void adc_init(void)
{

	//Enable the clock
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	// Select analog for pin
	PORTE->PCR[ADC_POS] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[ADC_POS] |= PORT_PCR_MUX(0);
	//Set the configuration of ADC
	ADC0->CFG1 = (ADC_CFG1_ADLPC_MASK | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE(3)
			| ADC_CFG1_ADICLK(0));

	//Set the status and control register
	ADC0->SC2 = (ADC_SC2_REFSEL(0));
	//Select the system options to ADC trigger enable
	//SIM->SOPT7 = (SIM_SOPT7_ADC0TRGSEL(9) | SIM_SOPT7_ADC0ALTTRGEN(1));
}

int read_ldr()
{
	ADC0->SC1[0] = 0x00; // start conversion on channel 0
	while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));
	ldr_value = ADC0->R[0];
	return ldr_value;
}
