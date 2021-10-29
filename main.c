#include "serial.h"
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BLINK_MS 500

int main () {
	DDRB |= (1<<PB3); // output pin
	
	while (true) {
		PORTB ^= (1<<PB3); // Using XOR to toggle between on and off.
		_delay_ms(BLINK_MS);
	}
}
