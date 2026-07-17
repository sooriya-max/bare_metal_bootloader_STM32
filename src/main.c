#include <stdint.h>
#include "flash_sector.h"
#include "uart.h"

/*CURRENT IMPLEMENTATION : uart_init() → uart_puts() → uart_receive_image() → CRC validate → flash_erase() → flash_write()*/

uint8_t recv_buf[FIRMWARE_MAX_SIZE];

int main()
{     

    char *uart_transmission = "Test For UART : Bootloader v1.0\n";
    uart_init();
    uart_puts(uart_transmission);
    uart_flush();

    uint32_t length = uart_receive_image(recv_buf, FIRMWARE_MAX_SIZE);
    if(length == 0)
    {
        uart_puts("CRC VALIDATION FAILED\r\n");
        while(1);
    }

    volatile uint32_t * dest = (volatile uint32_t *)0x08008000;             //This Location is chosen as this is Sector 2 in Flash Controller

    flash_unlock();
    flash_erase_sector(2);          //Erasing Sector 2
    flash_write(dest, (uint32_t *)recv_buf, length/4);
    /*length coming out of rec_buf is uint8_t, but flash_write writes uint32_t word and then loops it length times, which is why it is legth/4 times*/
    flash_lock();    

    uart_puts("FLASH OK\r\n");   

    
    return 0; 
}

