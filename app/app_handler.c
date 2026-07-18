#include <stdint.h>

extern uint32_t _sidata, _sdata, _edata; // for copying flash data to .data
extern uint32_t _sbss, _ebss;            // for zeroing out .bss

int app_main(void);
void Reset_Handler(void);

extern uint32_t _estack;

//Setting the Vector Table with word 0 as the Initial stack pointer and word 1 as the Reset Handler Address
__attribute__((section(".isr_vector"))) uint32_t vector_table[] = {(uint32_t)&_estack, (uint32_t)&Reset_Handler};

void Reset_Handler(void)
{  

    //copying Flash data to .data
    
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    
    while(dst < &_edata)
    {
        *dst++ = *src++;
    }
    
    //Zeroing .bss Section
    
    uint32_t *e_src = &_sbss;
    
    while(e_src < &_ebss)
    {
        *e_src++ = 0;
    }
    
    //Calling Main Function
    app_main(); 
    while(1); //THis Line Prevents Renode from going into a Hardfault, when main() Finishes and returns here
}