/*
 * adc.c
 *
 * Created: 9/3/2018 2:11:20 PM
 *  Author: swidmier
 */ 

#include <asf.h>
#include "adc.h"

void adc_init(void)
{
	ADCA.CTRLA = 0x01; // enable the ADC
	ADCA.CTRLB = 0x00; // unsigned 12 bit mode
	ADCA.REFCTRL = 0x10; // voltage Reference of Vcc/1.6V
	ADCA.PRESCALER = 0x05; // prescaler of DIV128 on the clock
	ADCA.CAL = adc_get_calibration_data(ADC_CAL_ADCA); // retrieve stored calibration data about the ADC
	
	ADCA.CH0.CTRL = 0x01; // single ended input
	ADCA.CH0.MUXCTRL = 0x00; // seading ADA pin 0	
}

uint16_t adc_read(void)
{
	ADCA.CH0.CTRL |= 0x80; // start the conversion
	while(!(ADCA.CH0.INTFLAGS)); // wait until the conversion is done
	return ADCA.CH0.RES; // return the 12-bit result as a uint16_t
}