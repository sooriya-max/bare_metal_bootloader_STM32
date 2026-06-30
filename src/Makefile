CPU ?= cortex-m4 

run: 
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -c main.c -o main.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -nostdlib -T ../boot.ld main.o -o main.elf


clean:
	rm -rf *.out *.elf *.lst *.debug *.o