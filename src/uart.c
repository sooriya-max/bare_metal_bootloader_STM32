#include "uart.h"
#include "CRC.h"
#include "ecdsa_verify.h"

#define UART2 ((volatile uint32_t *)0x40004400)


void uart_init(void)
{
    // 1. Enable clocks first
    volatile uint32_t *RCC_BASE_ADDR = (volatile uint32_t *)0x40023800;
    volatile uint32_t *RCC_AHB1ENR  = RCC_BASE_ADDR + 12;  // GPIOA clock
    volatile uint32_t *RCC_APB1ENR  = RCC_BASE_ADDR + 16;  // USART2 clock
    *RCC_AHB1ENR |= (1U << 0);
    *RCC_APB1ENR |= (1U << 17);

    
    volatile uint32_t *GPIO_A_BASE = (volatile uint32_t *)0x40020000;    
    volatile uint32_t *MODER       = GPIO_A_BASE + 0;       //This is to Say that this is Alternating Function
    volatile uint32_t *AFRL        = GPIO_A_BASE + 8;       //This is to Say that This is for UART_TX

    // 2. Configure PA2 as AF7
    *MODER |= (0b10 << 4);
    *AFRL  |= (0b0111 << 8);

    // 2. Configure PA3 as AF7
    *MODER |= (0b10 << 6);
    *AFRL  |= (0b0111 << 12);


    // 3. Configure USART2
    // BRR, CR1 — next
    volatile uint32_t *BRR      =   UART2 + 2;
    *BRR                        =   0x8AE;
    volatile uint32_t *CR1      =   UART2 + 3;
    *CR1                       |=   (1U << 2) | (1U << 3) | (1U << 13); // Bit 2 is for Reciever : Bit 3 is for Transmistter : Bit 13 is For UART

}

void uart_write(uint8_t data)
{
    volatile uint32_t *SR       =   UART2 + 0;              //This is to Initialize the Status Register of UART2
    volatile uint32_t *DR       =   UART2 + 1;              //This is to Initialize the Data Register of UART2
    
    while(!(*SR & (1U << 7)));     //Wait until the TXE is Ready                                     
    *DR = data;
}


uint8_t uart_getc(void)
{
    volatile uint32_t *SR       =   UART2 + 0;              //This is to Initialize the Status Register of UART2
    volatile uint32_t *DR       =   UART2 + 1;              //This is to Initialize the Data Register of UART2
    
    while(!(*SR & (1U << 5)));
    uint8_t data = *DR;
    return data;
}

void uart_puts(char *s)
{
    char *src = s;
    while(*src != '\0')
    {
        uart_write(*src);
        src++;
    }
}

void uart_flush(void)
{
    volatile uint32_t *SR       =   UART2 + 0;
    while(!(*SR & (1U << 6)));
}



uint32_t uart_receive_image(uint8_t *buf, uint32_t max_size)
{
    //1. wait for 0x69 Start bit
    while(!(uart_getc() == 0x69));

    //2. Getting the 4-byte length component
    uint32_t length = 0;
    uint32_t iterator = 0;
    while(iterator < 4)
    {
        length |= ((uint32_t)uart_getc() << (iterator * 8));
        iterator++;
    }

    //3. Getting the Length Field into buf
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
    
    //4. Getting the CRC word
    uint32_t CRC_length = 0;
    iterator = 0;
    while(iterator < 4)
    {
        CRC_length |= ((uint32_t)uart_getc() << (iterator * 8));
        iterator++;
    }

    //CRC Computation
    uint32_t received_crc = CRC_length;                  // what host sent    
    uint32_t computed_crc = crc32_compute(buf, length);  // what I calculated

    if(computed_crc != received_crc) 
    {
        uart_puts("CRC32 MISMATCH\n");
        return 0;
    }



    //5. ECDSA Signature Verification
    uint8_t ecdsa_signature[64];
    iterator = 0;
    while(iterator < 64)
    {
        ecdsa_signature[iterator] = uart_getc();            //Getting the Signature from the host into 64 bytes
        iterator++;
    }

    uint8_t ecdsa_result = ecdsa_verify(buf, length, ecdsa_signature);  //Verifying the ECDSA Signature from the ecdsa_verify.c
    if(!ecdsa_result)
    {
        uart_puts("ECDSA MISMATCH\n");
        return 0;
    }



    uart_puts("CRC32 or ECDSA MATCH\n");
    //Returning the Length parameter
    return length;    
}