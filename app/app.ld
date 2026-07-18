MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08008000, LENGTH = 0x100000
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 0x20000
}

_estack = ORIGIN(RAM) + LENGTH(RAM); /* This line can be anywhere except inside MEMORY Block and it represents top of stack */

SECTIONS
{ 
    .text :
    {
        *(.isr_vector*)
        *(.text*)
        *(.rodata*)
    } > FLASH
    
    .data :
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM AT> FLASH
    
    _sidata = LOADADDR(.data);
    
    .bss :
    {
        _sbss = .;
        *(.bss*)
        _ebss = .;
    } > RAM
    
}

