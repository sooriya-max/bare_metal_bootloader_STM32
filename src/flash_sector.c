#include <stdint.h>
#include "flash_sector.h"


void flash_unlock(void)
{
    volatile uint32_t *Flash_baseAddr = (0x40023C00);
    volatile uint32_t *FLASH_KEYR = Flash_baseAddr + 1;
    volatile uint32_t *FLASH_CR = Flash_baseAddr + 4;
    
    *FLASH_KEYR = 0x45670123;
    *FLASH_KEYR = 0xCDEF89AB;
    

}

void flash_erase_sector(uint8_t sector)
{
    volatile uint32_t *Flash_baseAddr = (0x40023C00);
    volatile uint32_t *FLASH_SR = Flash_baseAddr + 3;
    volatile uint32_t *FLASH_CR = Flash_baseAddr + 4;
    *FLASH_CR |= (1U << 1);
    
    *FLASH_CR &= ~(0xF << 3);   //For Clearing the Sector;
    *FLASH_CR |= (sector << 3); // For Programming the Given sector;
    *FLASH_CR |= (1U << 16);    // Setting the Start Bit which is in 16th pos
    
    
    while(*FLASH_SR & (1U << 16)); //Waiting for BSY bit to Clear
}

void flash_lock(void)
{
    volatile uint32_t *Flash_baseAddr = (0x40023C00);
    volatile uint32_t *FLASH_CR = Flash_baseAddr + 4;
    
    *FLASH_CR |= (1U << 31);
    
    
}