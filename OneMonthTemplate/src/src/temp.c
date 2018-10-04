/*
 * temp.c
 *
 * Created: 10/4/2018 6:04:30 PM
 *  Author: Sean
 */ 
#include "adc.h"

#include <math.h>
#include <asf.h>

#define A 0.003354016 // NTCLE1000E3103HT1
#define B 0.000256985
#define D 0.00000006383091 // don't really need C

float get_temperature(void)
{
	float voltage = (0.005*adc_read() - 0.09598); // some arbitrary y = mx+b	
	float res = (3.3*10000)/(3.3-voltage)-10000; // voltage division (Vcc*R1)/(Vcc-Vadc)
	return 1/(A+B*log(res/10000)+D*log(res/10000)*log(res/10000)*log(res/10000))); // Steinhart-Hart
}