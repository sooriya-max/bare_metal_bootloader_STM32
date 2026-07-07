#include <stdint.h>
#include "flash_sector.h"


int main()
{
    const uint32_t src[] = {0xDEADBEEF, 0xCAFEBABE, 0x12345678, 0xABCDABCD};
    volatile uint32_t * dest = (volatile uint32_t *)0x08008000;     //Sector 2 Address
    uint32_t length = 4;

    flash_unlock();
    flash_erase_sector(2);          //Erasing Sector 2
    flash_write(dest, src, length);
    flash_lock();
    
    return 0; 
}