#include "serial.h"
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BLINK_MS 500
#define BAUD 38400
#define FOSC 16000000
#define MYUBRR FOSC/16/BAUD-1

char txchar = 'H';

int main () {
	uart_init(MYUBRR); // initalise uart for transmit and receive.

	//DDRB |= (1<<PB3); // output pin
	
	while (true) {
		//PORTB ^= (1<<PB3); // Using XOR to toggle between on and off.
		//_delay_ms(BLINK_MS);
		uart_putchar(txchar);  // transmit character using txchar.
		_delay_ms(BLINK_MS);
	}
}
