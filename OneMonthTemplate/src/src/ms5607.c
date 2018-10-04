/*
 * ms5607.c
 *
 * Created: 9/3/2018 12:51:59 PM
 *  Author: cellis
 */ 

#include <asf.h>
#include "ms5607.h"
#include "spi_controller.h"

 /* Global Variable Declaration */
 uint16_t cal_pres_c1;
 uint16_t cal_pres_c2;
 uint16_t cal_pres_c3;
 uint16_t cal_pres_c4;
 uint16_t cal_pres_c5;
 uint16_t cal_pres_c6;
 
// this is a # define, it's a way to define a constant like a command that will never change
#define CMD_MS5607_READ_ADC	0x00

void ms5607_init(void)
{
	/* Calibrate value c1 */
	spi_select();
	spi_write(0b10100010); //prom read ad1
	cal_pres_c1 = ((uint16_t)spi_read())<<8; //bitshift
	cal_pres_c1 += ((uint16_t)spi_read());
	spi_deselect();

	/* Calibrate value c2 */
	spi_select();
	spi_write(0b10100100); //prom read ad2
	cal_pres_c2 = ((uint16_t)spi_read())<<8;
	cal_pres_c2 += ((uint16_t)spi_read());
	spi_deselect();

	/* Calibrate value c3 */
	spi_select();
	spi_write(0b10100110); //prom read ad3
	cal_pres_c3 = ((uint16_t)spi_read())<<8;
	cal_pres_c3 += ((uint16_t)spi_read());
	spi_deselect();

	/* Calibrate value c4 */
	spi_select();
	spi_write(0b10101000); //prom read ad4
	cal_pres_c4 = ((uint16_t)spi_read())<<8;
	cal_pres_c4 += ((uint16_t)spi_read());
	spi_deselect();

	/* Calibrate value c5 */
	spi_select();
	spi_write(0b10101010); //prom read ad5
	cal_pres_c5 = ((uint16_t)spi_read())<<8;
	cal_pres_c5 += ((uint16_t)spi_read());
	spi_deselect();

	/* Calibrate value c6 */
	spi_select();
	spi_write(0b10101100); //prom read ad6
	cal_pres_c6 = ((uint16_t)spi_read())<<8;
	cal_pres_c6 += ((uint16_t)spi_read());
	spi_deselect();
}

uint16_t ms5607_read_adc(void)
{
	uint16_t rx_data = 0; // temporary 16-bit value
	spi_select(); // select our spi device
	spi_write(CMD_MS5607_READ_ADC); // write a specified command to ask for data
	
	/*typecast this expression from an 8-bit to a 16-bit and shift it 8 bits to the left
	  meaning the returned value is now in the upper 8 bits rx_data*/
	rx_data = (uint16_t)spi_read()<<8; 
	
	// OR the second byte with the 16-bit variable, the returned value is now in the lower 8 bits of 'rx_data'
	rx_data |= spi_read(); 
	
	spi_deselect(); // end spi exchange
	
	return rx_data; // return the 16-bit value
}

int32_t get_pressure(void)
{
	/* Request current pressure value */
	spi_select();
	spi_write(0x48);
	spi_deselect();
	delay_ms(10);

	/* Read current pressure value */
	spi_select();
	spi_write(0x00);
	uint32_t uncal_pressure = ((uint32_t)spi_read())<<16; //Typecast the 8 bit data to 32 bit, then move it 16 places to the left. Stores in temp variable.
	uncal_pressure += ((uint32_t)spi_read())<<8; //Assign data to data + the new data but in the lower 8 bits.
	uncal_pressure += ((uint32_t)spi_read());
	spi_deselect();
	

	/* Request current temperature value */
	spi_select();
	spi_write(0x58); //Ask for temp value.
	spi_deselect();
	delay_ms(10);
	
	/* Read current temperature value */
	spi_select();
	spi_write(0x00);
	uint32_t d2 = ((uint32_t)spi_read())<<16;
	d2 += ((uint32_t)spi_read())<<8;
	d2 += ((uint32_t)spi_read());
	spi_deselect();
	
	/* Calculate temperature-adjusted pressure */
	int32_t dT = (int64_t)d2 - (((int64_t)cal_pres_c5)*(256));
	int64_t offset = ((int64_t)cal_pres_c2)*(65536) + ((((int64_t)cal_pres_c4)*((int64_t)dT))/(128));
	int64_t sens = (((int64_t)cal_pres_c1)*(32768)) + ((((int64_t)cal_pres_c3)*((int64_t)dT))/256);
	int32_t pressure = ((((int64_t)uncal_pressure) * (((uint64_t)sens)/2097152)) - (int64_t)offset)/32768;
	
	
	return pressure; //pressure given in pascals.
}