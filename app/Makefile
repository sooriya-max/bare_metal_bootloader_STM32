CPU ?= cortex-m4
APPLICATION ?= Application

run:
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c app_handler.c -o app_handler.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c app_main.c -o app_main.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c ../src/uart.c -o uart.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c ../src/CRC.c -o CRC.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c -I../lib/micro-ecc -I../lib/sha256 ../src/ecdsa_verify.c -o ecdsa_verify.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c -I../lib/micro-ecc ../lib/micro-ecc/uECC.c -o uECC.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c -I../lib/sha256 ../lib/sha256/sha256.c -o sha256.o

	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -nostdlib -T app.ld app_handler.o app_main.o uart.o CRC.o ecdsa_verify.o uECC.o sha256.o -o $(APPLICATION).elf -lc -lgcc

	arm-none-eabi-objdump -D -S $(APPLICATION).elf > $(APPLICATION).elf.lst
	arm-none-eabi-objcopy -O binary $(APPLICATION).elf $(APPLICATION).bin 


clean:
	rm -rf *.o *.out *.elf *.lst *.debug *.bin
