#include "serial.h"
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BLINK_MS 500
#define BAUD 38400
#define FOSC 16000000
#define UBRR FOSC/16/BAUD-1

//char txchar = 'H';
char *myname = "Neil Sawbridge\n";  // char array for testing putstr function


int main () {
	uart_init(UBRR); // initalise uart for transmit and receive.
	DDRB |= (1<<PB3); // output pin
	
		
	while (true) {
		uart_echo();

		_delay_ms(BLINK_MS);

	}
}
