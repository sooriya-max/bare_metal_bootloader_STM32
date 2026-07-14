CPU ?= cortex-m4 
PROCESSOR ?= olimex-stm32-h405
BOOTLOADER ?= Bootloader

run: 
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/flash_sector.c -o src/flash_sector.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/main.c -o src/main.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/Startup_c.c -o src/Startup_c.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/uart.c -o src/uart.o
	arm-none-eabi-as -mthumb -mcpu=$(CPU) -g -c src/Startup_s.S -o src/Startup_s.o	
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -nostdlib -T boot.ld src/main.o src/Startup_c.o src/Startup_s.o src/flash_sector.o src/uart.o -o src/$(BOOTLOADER).elf
	arm-none-eabi-objdump -D -S src/$(BOOTLOADER).elf > src/$(BOOTLOADER).elf.lst
	qemu-system-arm -S -M $(PROCESSOR) -display none -serial none -serial stdio -kernel src/$(BOOTLOADER).elf -gdb tcp::1234

gdb:
	gdb-multiarch -q $(BOOTLOADER).elf -ex "target remote localhost:1234"


clean:
	rm -rf *(.out*) *(.elf*) *.lst *.debug *.o


