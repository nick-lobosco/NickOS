AS=../cross/bin/i686-elf-as
GCC=../cross/bin/i686-elf-gcc
LD=../cross/bin/i686-elf-gcc -T linker.ld
GCCFLAGS=-Wno-unused -Wno-int-conversion -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc

TARGET = myos.bin
OBJECTS := $(patsubst %.c, %.o, $(shell find -type f -name "*.c")) boot.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)
	cp myos.bin isodir/boot/myos.bin
	grub-mkrescue -o myos.iso isodir
	rm $(OBJECTS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $^ -o $@

boot.o: boot.s
	$(AS) boot.s -o boot.o
	
clean:
	rm myos.bin myos.iso isodir/boot/myos.bin
