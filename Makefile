.PHONY: renode gdb clean

CPU ?= cortex-m4
BOOTLOADER ?= Bootloader

run:
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/flash_sector.c -o src/flash_sector.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/main.c -o src/main.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/Startup_c.c -o src/Startup_c.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/uart.c -o src/uart.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/CRC.c -o src/CRC.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/app_jump.c -o src/app_jump.o
	arm-none-eabi-as -mthumb -mcpu=$(CPU) -g -c src/Startup_s.S -o src/Startup_s.o
	
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -nostdlib -T boot.ld src/main.o src/Startup_c.o src/Startup_s.o src/flash_sector.o src/uart.o src/CRC.o src/app_jump.o -o $(BOOTLOADER).elf

	arm-none-eabi-objdump -D -S $(BOOTLOADER).elf > $(BOOTLOADER).elf.lst

renode:
	renode renode/boot.resc

gdb:
	gdb-multiarch -q $(BOOTLOADER).elf -ex "target remote localhost:1234"

clean:
	rm -rf src/*.o *.out *.elf *.lst *.debug