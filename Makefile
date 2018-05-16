make: boot.s kernel.c linker.ld
	../cross/bin/i686-elf-as boot.s -o boot.o
	../cross/bin/i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	../cross/bin/i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc 
	grub-mkrescue -o myos.iso isodir

clean:
	rm boot.o a.out kernel.o myos.bin myos.iso
