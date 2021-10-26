#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"
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


void uart_putchar(char chr) {
	/* Wait for empty transmit buffer */
 	while ( !( UCSR0A & (1<<UDRE0)) );
 	/* Put data into buffer, sends the data */
	UDR0 = chr;
	if (chr == '\n') {
		UDR0 = '\r'; // add carriage return if new line is sent.
	}
}

void uart_putstr(char *str)
{
	unsigned char j=0;
	char chr;
		
	while (str[j]!=0)		/* Send string till null */
	{
		uart_putchar(str[j]);	
		j++;
	}
}




