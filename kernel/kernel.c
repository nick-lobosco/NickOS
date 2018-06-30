#include "multiboot.h"
#include "libc/stdio.h"
 
/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)

#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
void getMemory(multiboot_info_t* mbt){
    multiboot_memory_map_t *map = (multiboot_memory_map_t*)mbt->mmap_addr;
	unsigned int i;
	for(i=0;i<mbt->mmap_length;i+=map->size+4){
		map=(multiboot_memory_map_t*)(mbt->mmap_addr+i);
		printf("size: %d   addr_low: %d   addr_high: %d   len_low: %d   len_high: %d   type: %d   ", map->size, map->addr_low, map->addr_high, map->len_low, map->len_high, map->type);
	}
	/*
	terminalWriteInt(1234);
	terminalPutchar('\n');
	terminalWriteInt(63456);
	terminalPutchar('\n');
	int length = mbt->mmap_length;	
	terminalWriteInt(length);
	terminalPutchar('\n');
    multiboot_memory_map_t *map = (multiboot_memory_map_t*)mbt->mmap_addr;
	int	i=0;
	while(i<length){
		terminalWriteString(" size: ");
		terminalWriteInt(map->size);
		terminalWriteString(" base: ");			
		terminalWriteInt(map->addr);
		terminalWriteString(" len: ");			
		terminalWriteAddress(map->len);
		terminalWriteString(" type: ");			
		terminalWriteInt(map->type);
		terminalPutchar('\n');
		i+=map->size+4;
    	multiboot_memory_map_t *map = (multiboot_memory_map_t*)(mbt->mmap_addr+i);
	}
	*/
}

void kernel_main(multiboot_info_t* mbt, unsigned int magic) 
{
	/* Initialize terminal interface */
	terminalInitialize();
	getMemory(mbt); 
//	printf("hello\nworld\n%d%s%d", 385, "hello", 12345);
//	terminalWrite_uint(1234);
	//getInput();
}




