#ifndef UART_H
#define UART_H
#define FIRMWARE_MAX_SIZE (96 * 1024)

#include <stdint.h>

void uart_init(void);
void uart_write(uint8_t data);
void uart_puts(char *s);
void uart_flush(void);
uint8_t uart_getc(void);
uint32_t uart_receive_image(uint8_t *buf, uint32_t max_size);


#endif