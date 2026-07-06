#ifndef FLASH_SECTOR_H
#define FLASH_SECTOR_H

#include <stdint.h>

void flash_unlock(void);
void flash_lock(void);
void flash_erase_sector(uint8_t sector);


#endif