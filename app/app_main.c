#include "../src/uart.h"

int app_main()
{
    uart_init();
    uart_puts("\nAPPLICATION IS RUNNING SUCCESSFULLY!!!\n");
    while(1);
    return 0;
}