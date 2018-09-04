/*
 * timer_counter.c
 *
 * Created: 7/28/2018 12:41:15 AM
 *  Author: cellis
 */ 

/* Begin #include section */
// this is where you will need to include the header files that you have written functions in to use them
#include <asf.h> // this will include code that you imported from ASF wizard
#include "timer_counter.h"

void timer_counter_init(uint16_t period)
{
	sysclk_enable_peripheral_clock(&TCE0);	// remember to enable the peripheral clock for this timer/counter
	
	TCE0.CTRLA = 0x07;	// set the timer/counter prescaler to be the CPU clock divided by 1024 in CTRLA
	TCE0.PER = period;	// set the period register to the period we gave as an argument
	TCE0.INTCTRLA = TC_OVFINTLVL_LO_gc; // enable low level interrupts for overflow on this timer/counter
}

// this interrupt is called each time the timer/counter overflows
ISR(TCE0_OVF_vect)
{
	PORTQ.OUT ^= 0x08;	// toggle LED0 on the xplained board
}
