#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"
#include <stddef.h>
#include <string.h>

#define BAUD 38400
#define FOSC 16000000
#define BLINK_MS 500

void uart_init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr>>8);
 	UBRR0L = (unsigned char)ubrr;
 	//Enable receiver and transmitter */
 	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 	/* Set frame format: 8data, 1stop bit */
 	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

void uart_UDRE(char chr) {
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = chr;
}


void uart_putchar(char chr) {
	/* Wait for empty transmit buffer */
 	uart_UDRE(chr); // assign chr to UDR0.

	if (chr == '\n') {
		uart_UDRE('\r'); // add carriage return if new line is sent.
	}
}

void uart_putstr(char *str)
{
	unsigned char j=0;
			
	while (str[j]!=0)		/* Send string till null */
	{
		uart_putchar(str[j]);	
		j++;
	}
}

char uart_getchar(void) {
	while (!( UCSR0A & (1<<RXC0))) { }; // Do nothing until data have been received
	// Return data from register UDR0.
	return UDR0;
}

char uart_echo() {
	char echoData;
	echoData = uart_getchar();
	_delay_ms(500);
	uart_putchar(echoData);
	return echoData;
}

void ledONOFF() {
	int index = 0;
	char inputBuffer[100];
	char newCharacter;

	while (1) {
		newCharacter = uart_echo();
		if (newCharacter == '\r' || newCharacter == '\n') {
			inputBuffer[index++] = '\0'; // add '\0' to intputbuffer so strcmp can function
			if (!strcmp(inputBuffer, "on")) {
				PORTB &= ~(1 << PORTB3); // Led on.
				_delay_ms(500);
			}
			if (!strcmp(inputBuffer, "off")) {
				PORTB |= (1 << PORTB3); // Led Off.
				_delay_ms(500);
			}
			index = 0; // Reset index after command processed.
			memset(inputBuffer, 0, sizeof(inputBuffer));  // reset intputBuffer.
			uart_UDRE('\n'); // Send a new line to the terminal.

		} else {
			inputBuffer[index++] = newCharacter;
		}
	}        
}
	





