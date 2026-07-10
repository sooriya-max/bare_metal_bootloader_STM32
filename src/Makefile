CPU ?= cortex-m4 

run: 
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c flash_sector.c -o flash_sector.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c main.c -o main.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c Startup_c.c -o Startup_c.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c uart.c -o uart.o
	arm-none-eabi-as -mthumb -mcpu=$(CPU) -g -c Startup_s.S -o Startup_s.o	
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -nostdlib -T ../boot.ld main.o Startup_c.o Startup_s.o flash_sector.o uart.o -o Bootloader.elf
	arm-none-eabi-objdump -D -S Bootloader.elf > Bootloader.elf.lst
	qemu-system-arm -S -M olimex-stm32-h405 -display none -serial none -serial stdio -kernel Bootloader.elf -gdb tcp::1234

gdb:
	gdb-multiarch -q Bootloader.elf -ex "target remote localhost:1234"


clean:
	rm -rf *.out *.elf *.lst *.debug *.o


