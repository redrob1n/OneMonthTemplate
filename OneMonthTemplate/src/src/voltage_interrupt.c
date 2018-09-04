/*
 * voltage_interrupt.c
 *
 * Created: 9/3/2018 2:33:55 PM
 *  Author: swidmier
 */ 

#include <asf.h>
#include "voltage_interrupt.h"

void interrupt_init(void)
{
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;	// Allow low, medium, high level interrupts globally
	sei(); // set enable interrupts globally
	
	PORTA.DIR &= ~0x01; // set pin 0 to input
	PORTA.PIN0CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc; // enable pullup group configuration and falling-edge interrupts on port A pin 0
	PORTA.INT0MASK = 0x01; // mask interrupt 0 (INT0) to pin 0.
	PORTA.INTCTRL = PORT_INT0LVL_LO_gc; // set the level of interrupt 0 to low.
}

ISR(PORTA_INT0_vect)
{
	PORTQ.OUT ^= 0x08; // toggle the LED on PortQ
	delay_ms(100);
	PORTQ.OUT ^= 0x08; // toggle the LED again
}