CPU ?= cortex-m4 

run: 
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -c main.c -o main.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -c Startup_c.c -o Startup_c.o
	arm-none-eabi-as -mthumb -mcpu=$(CPU) -c Startup_s.S -o Startup_s.o
	arm-none-eabi-gcc -mthumb -mcpu=$(CPU) -nostdlib -T ../boot.ld main.o Startup_c.o Startup_s.o -o main.elf


clean:
	rm -rf *.out *.elf *.lst *.debug *.o


