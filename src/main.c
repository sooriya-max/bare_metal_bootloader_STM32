#include <stdint.h>
#include "flash_sector.h"
#include "uart.h"

int main()
{
    const uint32_t src[] = {0xDEADBEEF, 0xCAFEBABE, 0x12345678, 0xABCDABCD};
    volatile uint32_t * dest = (volatile uint32_t *)0x20002000;     
    //RAM Address - 0x20000000
    //Sector 2 Address - 0x08008000; But could not emulate as qemu does not support for flash registers
    /*Instead of Relying on QEMU Flash Registers, which does not exist, changing the address to RAM path, to see if the given pattern is visible or not*/
    /* code verified against RM0090, hardware path validated on real silicon would be the next step.*/
    uint32_t length = 4;

    char *uart_transmission = "Bootloader v1.0";
    uart_init();
    uart_puts(uart_transmission);
    uart_flush();

    flash_unlock();
    flash_erase_sector(2);          //Erasing Sector 2
    flash_write(dest, src, length);
    flash_lock();

    

    
    return 0; 
}