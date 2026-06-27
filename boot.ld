MEMORY
{
    FLASH : ORIGIN = 0x08000000, LENGTH = 0x100000
    RAM   : ORIGIN = 0x20000000, LENGTH = 0x20000
}


SECTIONS
{
 
     .text
    {
        *(.isr_vector*)
        *(.text*)
    } > FLASH
    
    .data
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM AT> FLASH
    
    _sidata = LOADADDR(.data);
    
    .bss
    {
        _sbss = .;
        *(.bss*)
        _ebss =.;
    } > RAM
    
}

