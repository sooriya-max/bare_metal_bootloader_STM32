#include <stdint.h>

void uart_init(void)
{
    // Step 1 — enable USART2 clock via RCC
    volatile uint32_t *RCC_BASE_ADDR = (volatile uint32_t *)0x40023800;
    volatile uint32_t *RCC_APB1ENR   = RCC_BASE_ADDR + 16;
    *RCC_APB1ENR |= (1U << 17);

    // Step 2 — load BRR
    volatile uint32_t *USART2_BRR = ;
    *USART2_BRR = 0x8AE;

    // Step 3 — enable USART2 and TX via CR1


    // Step 4 — uart_write() polling loop
}


