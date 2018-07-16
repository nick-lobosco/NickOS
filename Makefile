GCCFLAGS="-Wno-unused"

make: boot.s kernel/kernel.c kernel/terminal/terminal.c kernel/libc/string.c kernel/libc/stdio.c kernel/libc/Math.c linker.ld
	../cross/bin/i686-elf-as boot.s -o boot.o
	../cross/bin/i686-elf-gcc $(GCCFLAGS) -c kernel/kernel.c kernel/terminal/terminal.c kernel/libc/string.c kernel/libc/stdio.c kernel/libc/Math.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	../cross/bin/i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o terminal.o stdio.o string.o Math.o -lgcc 
	cp myos.bin isodir/boot/myos.bin
	grub-mkrescue -o myos.iso isodir
	rm *.o

clean:
	rm myos.bin myos.iso isodir/boot/myos.bin
