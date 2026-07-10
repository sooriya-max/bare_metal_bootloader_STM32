#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init(void);
void uart_write(uint8_t data);
void uart_puts(char *s);
void uart_flush(void);


#endif