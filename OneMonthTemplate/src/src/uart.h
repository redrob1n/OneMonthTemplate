/*
 * uart.h
 *
 * Created: 9/3/2018 12:23:05 PM
 *  Author: Sean
 */ 

#ifndef  UART_H_
#define UART_H_

#include <asf.h>

#define UART_TERMINAL_SERIAL			&USARTE0
#define UART_TERMINAL_SERIAL_BAUDRATE	9600
#define UART_TERMINAL_SERIAL_CHAR_LEN	USART_CHSIZE_8BIT_gc
#define UART_TERMINAL_SERIAL_PARITY		USART_PMODE_DISABLED_gc
#define UART_TERMINAL_SERIAL_STOP_BIT	true

#define UART_TERMINAL_TX_PIN			PIN3_bm
#define UART_TERMINAL_PORT				PORTE

void uart_terminal_init(void);

#endif UART_H_