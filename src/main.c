#include <stdint.h>
#include "flash_sector.h"
#include "uart.h"

#define FIRMWARE_MAX_SIZE (96 * 1024)
uint8_t recv_buf[FIRMWARE_MAX_SIZE];

int main()
{
    const uint32_t src[] = {0xDEADBEEF, 0xCAFEBABE, 0x12345678, 0xABCDABCD};
    volatile uint32_t * dest = (volatile uint32_t *)0x08008000;     
    //RAM Address - 0x20000000
    //Sector 2 Address - 0x08008000; But could not emulate as qemu does not support for flash registers
    /*Instead of Relying on QEMU Flash Registers, which does not exist, changing the address to RAM path, to see if the given pattern is visible or not*/
    /* code verified against RM0090, hardware path validated on real silicon would be the next step.*/
    uint32_t length = 4;

    flash_unlock();
    flash_erase_sector(2);          //Erasing Sector 2
    flash_write(dest, src, length);
    flash_lock();

    char *uart_transmission = "Test For UART : Bootloader v1.0\n";
    uart_init();
    uart_puts(uart_transmission);
    uart_flush();

    //This is a Echo Test with a single character from Rx to Tx
    uint8_t ch = uart_getc();
    uart_puts("UART CHARACTER <");
    uart_write(ch);
    uart_puts("> GOT IT");    

    
    return 0; 
}

uint32_t uart_receive_image(uint8_t *buf, uint32_t max_size)
{
    // wait for 0x69 Start bit
    while(!(uart_getc() == 0x69));

    //Getting the 4-byte length component
    uint32_t length = 0;
    uint8_t iterator = 0;
    while(iterator < 4)
    {
        length |= ((uint32_t)uart_getc() << (iterator * 8));
        iterator++;
    }

    //Getting the Length Field into buf
    if(length > FIRMWARE_MAX_SIZE)
    {
        return 0;               //This 0 will go to the length fields of flash write saying that this is a failure
    }
    iterator = 0;
    while(iterator < length)
    {
        buf[iterator]= uart_getc();
        iterator++;
    }
    
    //Getting the CRC word
    uint32_t CRC_length = 0;
    iterator = 0;
    while(iterator < 4)
    {
        CRC_length |= ((uint32_t)uart_getc() << (iterator * 8));
        iterator++;
    }

    //Returning the Length parameter
    return length;    
}