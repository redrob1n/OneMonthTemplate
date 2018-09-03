/*
*
*/
#include <asf.h>
#include "include/timer_counter.h"
#include "include/uart.h"

void TCE0_init(uint16_t period);
void initialize_interrupt(void);

int main (void)
{
	board_init();

	/* Insert application code here, after the board has been initialized. */
	sysclk_init();
	
	//PORTE.DIR = 0xFF;
	//PORTE.OUT = 0xFF;
	
	//timer_counter_init(31249);
	
// 	PMIC.CTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PORT_INT0LVL_LO_gc;
// 	
// 	
// 	sei();
// 	
// 	PORTQ.DIR = 0x08; // sets the LED on PORTQ pin 3 to output	
	uart_terminal_init();
	printf("hello\n");
	printf("world\n");
// 	PORTQ.DIR = 0x08; //Set PORTQ pin 3 direction to output
// 	PORTQ.OUT = 0x08; // Set PORTQ pin 3 output to 1 i.e. LED is off
// 	
// 	initialize_interrupt(); //function call for initialize_interrupt()
	
	/* infinite loop */
	for(;;)
	{
		//printf("Hello world\n");
// 		PORTQ.OUT = 0x00; //turn PQ3 LED on
// 		delay_ms(2000);
// 		PORTQ.OUT |= 0x08; //turn PQ3 LED off
// 		delay_ms(2000);
	}
	
	//never go here pls
}

ISR(PORTA_INT0_vect)
{
	PORTQ.OUT ^= 0x08; // Toggle the LED on PortQ
	delay_ms(100);
	PORTQ.OUT ^= 0x08; // toggle the LED again
}

void initialize_interrupt(void)
{
	/* Initialization for all interrupts */
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm; // Allow low, medium, high level interrupts
	sei(); //set enable interrupts
	
	/* Initialize Port A Pin 0 interrupt */
	PORTA.DIR &= ~0x01; // Set pin 0 to input
	PORTA.PIN0CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc; // Enable pullup group configuration and falling-edge interrupts on port A pin 0
	PORTA.INT0MASK = 0x01; // Mask interrupt 0 (INT0) to pin 0.
	PORTA.INTCTRL = PORT_INT0LVL_LO_gc; // Set the level of interrupt 0 to low.
}




void TCE0_init(uint16_t period)
{
	sysclk_enable_peripheral_clock(&TCE0); // always enable the peripherial's clock
	sysclk_enable_module(SYSCLK_PORT_E, SYSCLK_HIRES); // this line must be added for waveform outputs to work
	
	/* Example using PORTE pin 0 */
	PORTE.DIR = 0x01;  // set pin 0 to output
	TCE0.CTRLA = 0x07; // 0110 is prescaler 256
	TCE0.CTRLB = 0x13; // Timer/Counter output A (PORTE pin 0) enabled and single slope pwm
	TCE0.PER = 12499; // Timer/counter period for 10 Hz
	TCE0.CCA = TCE0.PER - (TCE0.PER / 10); // 90% duty cycle is 10% on time for LEDs
}



