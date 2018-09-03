/*
 * ms5607.c
 *
 * Created: 9/3/2018 12:51:59 PM
 *  Author: cellis
 */ 
#include <asf.h>
#include "include/ms5607.h"
#include "include/spi_controller.h"
// this is a # define, it's a way to define a constant like a command that will never change
#define CMD_MS5607_READ_ADC	0x00


uint16_t ms5607_read_adc(void)
{
	uint16_t rx_data = 0; // temporary 16-bit value
	spi_select(); // select our spi device
	spi_write(CMD_MS5607_READ_ADC); //write a specified command to ask for data
	
	/*typecast this expression from an 8-bit to a 16-bit and shift it 8 bits to the left
	  meaning the returned value is now in the upper 8 bits rx_data*/
	rx_data = (uint16_t)spi_read()<<8; 
	
	//or the second byte with the 16-bit variable, the returned value is now in the lower 8 bits of 'rx_data'
	rx_data |= spi_read(); 
	
	spi_deselect(); // end spi exchange
	
	return rx_data; //return the 16-bit value
}