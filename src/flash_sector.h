#ifndef FLASH_SECTOR_H
#define FLASH_SECTOR_H

#include <stdint.h>

void flash_unlock(void);
void flash_lock(void);
void flash_erase_sector(uint8_t sector);
void flash_write(volatile uint32_t *dest, const uint32_t *src, uint32_t length)


#endif