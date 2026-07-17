#ifndef CRC_H
#define CRC_H

#include <stdint.h>

uint32_t crc32_compute(uint8_t uart_bytes[], uint32_t length);

#endif