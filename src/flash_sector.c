#include <stdint.h>
#include "flash_sector.h"

#define FLASH_BASE ((volatile uint32_t *)0x40023C00)

void flash_unlock(void)
{
    volatile uint32_t *FLASH_KEYR = FLASH_BASE + 1;
    volatile uint32_t *FLASH_CR = FLASH_BASE + 4;
    
    *FLASH_KEYR = 0x45670123;   //Writing the First Key into the Control Register
    *FLASH_KEYR = 0xCDEF89AB;   //Writing the Second Key into the Control Register
    

}

void flash_erase_sector(uint8_t sector)
{
    volatile uint32_t *FLASH_SR = FLASH_BASE + 3;
    volatile uint32_t *FLASH_CR = FLASH_BASE + 4;
    *FLASH_CR |= (1U << 1);
    
    *FLASH_CR &= ~(0xF << 3);   //For Clearing the Sector;
    *FLASH_CR |= (sector << 3); // For Programming the Given sector;
    *FLASH_CR |= (1U << 16);    // Setting the Start Bit which is in 16th pos
    
    
    while(*FLASH_SR & (1U << 16)); //Waiting for BSY bit to Clear
}

void flash_lock(void)
{
    volatile uint32_t *FLASH_CR = FLASH_BASE + 4;
    
    *FLASH_CR |= (1U << 31);    //Locking the Flash after Clearing
    
    
}