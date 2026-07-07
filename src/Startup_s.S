.section .isr_vector, "a"

.extern _estack

.word _estack
.word Reset_Handler
.word NMI_Handler
.word HardFault_Handler
.word MemManage_Handler


MemManage_Handler :
NMI_Handler :
HardFault_Handler :
    b .
