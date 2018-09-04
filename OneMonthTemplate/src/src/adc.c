/*
 * adc.c
 *
 * Created: 9/3/2018 2:11:20 PM
 *  Author: Sean
 */ 
#include <asf.h>
#include "include/adc.h"

void adc_init(void)
{
	ADCA.CTRLA = 0x01;				// Enables the ADC
	ADCA.CTRLB = 0x00;				// Unsigned 12 bit mode
	ADCA.REFCTRL = 0x10;			// Voltage Reference of Vcc/1.6V
	ADCA.PRESCALER = 0x05;			// This is an automatic prescaler of 128 on the clock
	ADCA.CAL = adc_get_calibration_data(ADC_CAL_ADCA); //retrieve stored calibration data about the ADC
	
	ADCA.CH0.CTRL = 0x01;			// Single ended input
	ADCA.CH0.MUXCTRL = 0x00;		// Reading ADA pin 0	
}

uint16_t adc_read(void)
{
	ADCA.CH0.CTRL |= 0x80;			// Start the conversion
	while(!(ADCA.CH0.INTFLAGS));	// Wait until the conversion is done
	return ADCA.CH0.RES;			// Return the 12-bit result as a uint16_t
}