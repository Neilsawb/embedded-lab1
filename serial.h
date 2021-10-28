#ifndef SERIAL_H_
#define SERIAL_H_

void uart_init(unsigned int ubrr);
void uart_putchar(char chr);
void uart_putstr(char *str);

char uart_getchar(void);

char uart_echo(void);
void uart_UDRE(char chr);
void ledONOFF();

#endif

