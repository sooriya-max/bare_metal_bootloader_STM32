#include <stdint.h>
#include "flash_sector.h"

int main()
{
    const uint32_t src[] = {0xDEADBEEF, 0xCAFEBABE, 0x12345678, 0xABCDABCD};
    volatile uint32_t * dest = (volatile uint32_t *)0x20000000;     
    //RAM Address - 0x20000000
    //Sector 2 Address - 0x08008000; But could not emulate as qemu does not support for flash registers
    /*Instead of Relying on QEMU Flash Registers, which does not exist, changing the address to RAM path, to see if the given pattern is visible or not*/
    /* code verified against RM0090, hardware path validated on real silicon would be the next step.*/
    uint32_t length = 4;

    flash_unlock();
    flash_erase_sector(2);          //Erasing Sector 2
    flash_write(dest, src, length);
    flash_lock();
    
    return 0; 
}