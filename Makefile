make: boot.s kernel.c linker.ld
	../cross/bin/i686-elf-as boot.s -o boot.o
	../cross/bin/i686-elf-gcc -c kernel.c terminal.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	../cross/bin/i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o terminal.o -lgcc 
	cp myos.bin isodir/boot/myos.bin
	grub-mkrescue -o myos.iso isodir

clean:
	rm boot.o kernel.o terminal.o myos.bin myos.iso isodir/boot/myos.bin
