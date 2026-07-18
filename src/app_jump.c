#include <stdint.h>

void app_jump(void)
{
    //disables all interrupts, writes 1 to PRIMASK register ; cpsid : Change Processor State, Interrupt Disable
    __asm__ volatile ("cpsid i");
    
    //Physical address of Vector Table Register in System control block ; SCB -> VTOR
    *((volatile uint32_t*)0xE000ED08) = 0x08008000;
    
    //reads word 0 of the VTOR
    uint32_t app_sp = *(uint32_t *)0x08008000;
    
    //Move into System register, the msp is the destination, %0 means its a place holder for (app_sp) - Application Stack pointer, "r" put this into genral purpose register
    /*
    the r3 is taken as an example here
    ldr r3, val      ← load val into r3
    msr msp, r3      ← move r3 into MSP
    
    */
    __asm__ volatile ("msr msp, %0": : "r"(app_sp));
    
    //Calling the address from word 1 by casting that data into function pointer and calling it
    uint32_t app_reset = *(uint32_t *)0x08008004;  // read Reset_Handler address
    void (* app_reset_handler)(void) = (void (*)(void))(app_reset | 0x1); //setting thumb bit 1
    app_reset_handler();
}
