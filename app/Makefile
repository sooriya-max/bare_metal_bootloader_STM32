CPU ?= cortex-m4
APPLICATION ?= Application

run:
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c app_handler.c -o app_handler.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c app_main.c -o app_main.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c ../src/uart.c -o uart.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -g -c ../src/CRC.c -o CRC.o

	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -nostdlib -T app.ld app_handler.o app_main.o uart.o CRC.o -o $(APPLICATION).elf

	arm-none-eabi-objdump -D -S $(APPLICATION).elf > $(APPLICATION).elf.lst
	arm-none-eabi-objcopy -O binary $(APPLICATION).elf $(APPLICATION).bin 

renode:
	renode renode/boot.resc

gdb:
	gdb-multiarch -q $(APPLICATION).elf -ex "target remote localhost:1234"

clean:
	rm -rf *.o *.out *.elf *.lst *.debug *.bin