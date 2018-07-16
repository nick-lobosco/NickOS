#include "multiboot.h"
#include "libc/stdio.h"
#include "terminal/terminal.h"
#include <stdint.h> 

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)

#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

typedef struct gdtentry GDTE;
 struct gdtentry{
	short limit1;
	short base1;
	char base2;
	char access;
	char flags;
	char base3;
}__attribute__((packed));


struct gdtDescriptor{
	short size;
	unsigned int gdtPtr;
}__attribute__((packed));
typedef struct gdtDescriptor GDTD;

typedef struct idtd{
	short size;
	int address;
}IDTD;

typedef struct idtEntry{
	uint16_t offset1;
	uint16_t selector;
	uint8_t zero;
	uint8_t type_attr;
	uint16_t offset2;
}IDTE;

extern GDTD gdtDescriptor;
extern GDTE gdt;

void printGdtEntry(GDTE *gdte){
	printf("%d %d %d %d %d %d\n", gdte->limit1, gdte->base1, gdte->base1, gdte->access, gdte->flags, gdte->base3);
}

void printGDT(GDTD *gdtd){
	printf("%d\n%d\n",gdtd->size, gdtd->gdtPtr);
	int i;
	for(i=0;i<(gdtd->size);i+=8){
		printGdtEntry((GDTE*)(gdtd->gdtPtr+i));
	}
}

void getMemory(multiboot_info_t* mbt){
    multiboot_memory_map_t *map = (multiboot_memory_map_t*)mbt->mmap_addr;
	unsigned int i;
	for(i=0;i<mbt->mmap_length;i+=map->size+4){
		map=(multiboot_memory_map_t*)(mbt->mmap_addr+i);
		printf("size: %d   addr_low: %d   addr_high: %d   len_low: %d   len_high: %d   type: %d\n",
			map->size, map->addr_low, map->addr_high, map->len_low, map->len_high, map->type);
	}
}

void kernel_main(multiboot_info_t* mbt, unsigned int magic) 
{
	/* Initialize terminal interface */
	terminalInitialize();
	while(1);
	/*
	printf("%d\n", &gdt);
	printf("%d\n", gdtDescriptor.gdtPtr);
	printf("\n\n");
	printGDT(&gdtDescriptor);
	*/
}




