/*
 * voltage_interrupt.c
 *
 * Created: 9/3/2018 2:33:55 PM
 *  Author: Sean
 */ 

ISR(PORTA_INT0_vect)
{
	PORTQ.OUT ^= 0x08; // Toggle the LED on PortQ
	delay_ms(100);
	PORTQ.OUT ^= 0x08; // toggle the LED again
}

void initialize_interrupt(void)
{
	/* Initialization for all interrupts */
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;	// Allow low, medium, high level interrupts
	sei(); // set enable interrupts
	
	/* Initialize Port A Pin 0 interrupt */
	PORTA.DIR &= ~0x01; // Set pin 0 to input
	PORTA.PIN0CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc; // Enable pullup group configuration and falling-edge interrupts on port A pin 0
	PORTA.INT0MASK = 0x01; // Mask interrupt 0 (INT0) to pin 0.
	PORTA.INTCTRL = PORT_INT0LVL_LO_gc; // Set the level of interrupt 0 to low.
}