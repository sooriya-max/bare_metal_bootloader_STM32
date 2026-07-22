.PHONY: renode gdb clean

CPU ?= cortex-m4
BOOTLOADER ?= Bootloader

run:
#	Object File Conversion Lines
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/flash_sector.c -o src/flash_sector.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/main.c -o src/main.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/Startup_c.c -o src/Startup_c.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/uart.c -o src/uart.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/CRC.c -o src/CRC.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c src/app_jump.c -o src/app_jump.o
	arm-none-eabi-as -mthumb -mcpu=$(CPU) -g -c src/Startup_s.S -o src/Startup_s.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c -Ilib/micro-ecc -Ilib/sha256 src/ecdsa_verify.c -o src/ecdsa_verify.o

#	Addition of Two .c files that are not built by me. the -I is for including the Header Search path (i.e  where to search for the hearder file).
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c -Ilib/micro-ecc lib/micro-ecc/uECC.c -o lib/micro-ecc/uECC.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c -Ilib/sha256 lib/sha256/sha256.c -o lib/sha256/sha256.o
#	Compilation Line	
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -nostdlib -T boot.ld src/main.o src/Startup_c.o src/Startup_s.o src/flash_sector.o src/uart.o src/CRC.o src/app_jump.o src/ecdsa_verify.o lib/micro-ecc/uECC.o lib/sha256/sha256.o -o $(BOOTLOADER).elf -lc -lgcc

	arm-none-eabi-objdump -D -S $(BOOTLOADER).elf > $(BOOTLOADER).elf.lst

renode:
	renode renode/boot.resc

gdb:
	gdb-multiarch -q $(BOOTLOADER).elf -ex "target remote localhost:1234"

clean:
	rm -rf src/*.o lib/micro-ecc/*.o lib/sha256/*.o *.out *.elf *.lst *.debug
