#include <stdint.h>

void uart_init(void)
{
    // 1. Enable clocks first
volatile uint32_t *RCC_BASE_ADDR = (volatile uint32_t *)0x40023800;
volatile uint32_t *RCC_AHB1ENR  = RCC_BASE_ADDR + 12;  // GPIOA clock
volatile uint32_t *RCC_APB1ENR  = RCC_BASE_ADDR + 16;  // USART2 clock
*RCC_AHB1ENR |= (1U << 0);
*RCC_APB1ENR |= (1U << 17);

// 2. Configure PA2 as AF7
volatile uint32_t *GPIO_A_BASE = (volatile uint32_t *)0x40020000;
volatile uint32_t *MODER       = GPIO_A_BASE + 0;       //This is to Say that this is Alternating Function
volatile uint32_t *AFRL        = GPIO_A_BASE + 8;       //This is to Say that This is for UART_TX
*MODER |= (0b10 << 4);
*AFRL  |= (0b0111 << 8);

// 3. Configure USART2
// BRR, CR1 — next
}


