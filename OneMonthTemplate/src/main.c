/*
 * timer_counter.c
 *
 * Created: 7/28/2018 12:40:05 AM
 *  Author: cellis
 */ 

#include <asf.h>
#include "include/timer_counter.h"
#include "include/uart.h"

static void system_initialize(void)
{
	
}

int main (void)
{
	sysclk_init(); //enable the system clock, must be done first, clock settings are found in config->conf_clock.h
	
	system_initialize(); //function in which we will put our initialization code
	
	/* Infinite loop */
	for(;;)
	{
		
	}
}