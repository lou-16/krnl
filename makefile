GPPPARAMS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = loader.o kernel.o

%.o: %.c
	i686-elf-gcc $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	i686-elf-as -o $@ $<
	
krnl.bin: 
	i686-elf-gcc -T linker.ld -o $@ -nostdlib $(objects) -lgcc

install: krnl.bin 
	
run: krnl.bin
	qemu-system-i386 