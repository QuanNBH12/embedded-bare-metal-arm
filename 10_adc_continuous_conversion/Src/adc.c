#include "adc.h"

#define GPIOAEN 	(1U << 0) // Register enable clock for GPIO
#define ADC1EN		(1U << 8) // Register enable clock RCC for ADC module
#define ADC_CH1		(1U << 0)	// Register setup memory for sequence start (1 channel: SQ1; 2 channel: SQ2...)
#define ADC_SEQ_LEN		(0x00) // Register set up sequence length ADC (1->xx channels)
#define CR2_ADON	(1U << 0) // Register ON/OFF A/D Converter Module
#define CR2_SWSTART	(1U << 30) // Register start regular conversion channels
#define SR_EOC		(1U << 1) // Register manage end of conversion of regular channels. Maybe config EOC or EOS (End of sequence)
#define CR2_CONT	(1U << 1) // Register define A/D Converter Continuous


void pa1_adc_init(){
	/* Configuration GPIOA pin */
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set the mode PA1 to analog
	GPIOA->MODER |= (1U << 2);
	GPIOA->MODER |= (1U << 3);

	/* Configuration ADC module */
	/* Enable clock to access to ADC */
	RCC->APB2ENR |= ADC1EN;

	/* Conversion sequence start */
	ADC1->SQR3 |= ADC_CH1;

	/* Set up number of conversion channel */
	ADC1->SQR1 = ADC_SEQ_LEN;

	/* Enable ADC Module (ON/OFF A/D Converter) */
	ADC1->CR2 |= CR2_ADON;

}

void start_conversion(){
	// Enable continuous conversion
	ADC1->CR2 |= CR2_CONT;

	// Start ADC Conversion
	ADC1->CR2 |= CR2_SWSTART;

}

uint32_t adc_read(){

	// while register SR EOC not become 1, continue waiting
	while (!(ADC1->SR & SR_EOC)){}
	// read data ADC result
	return ADC1->DR;
}







