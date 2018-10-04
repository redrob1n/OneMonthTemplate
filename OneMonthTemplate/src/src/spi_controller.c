/*
 * spi_controller.c
 *
 * Created: 9/3/2018 12:50:35 PM
 *  Author: cellis
 */ 

#include <asf.h>
#include "spi_controller.h"

void spi_init(void)
{
	PORTC.DIR |= 0b10110000; //Set port to input.
	PORTC.DIR &= 0b10111111;
	SPIC.CTRL = 0b01010000; //Clock Double off, enable SPI, MSB DORD, master mode, SPI transfer mode set to 0, prescalar set to clkper/4 (has no effect in slave mode).
}

void spi_select(void)
{
	PORTC.OUT &= 0b11101111;
}

void spi_deselect(void)
{
	PORTC.OUT |= 0b00010000;
}

uint8_t spi_read(void)
{
	SPIC.DATA = 0xFF; // make the DATA register something we know
	while(!(SPIC.STATUS>>7)); // wait for the SPI interrupt flag to let us know the transfer is complete
	
	return SPIC.DATA; // return the data from this function
}

void spi_write(uint8_t data)
{
	SPIC.DATA = data; // write the data we want to send to the data register
	while(!(SPIC.STATUS>>7)); // wait to ensure the data is sent before we do anything else
}