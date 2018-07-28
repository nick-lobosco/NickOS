#include "multiboot.h"
#include "libc/stdio.h"
#include "terminal/terminal.h"
#include <stdint.h> 
#include "tables.h"
#include "kernel.h"
#include "memory/memory.h"

extern int mbStart;
extern int mbEnd;
extern int bssStart;
extern int bssEnd;
extern int textStart;
extern int textEnd;
extern int dataStart;
extern int dataEnd;

extern int stack_bottom;
extern int cont;
extern int gdt;
/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)

#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif



void memset(char* mem, char c, size_t size){
	size_t i;
	for(i=0;i<size;i++){
		mem[i]=c;
	}
}




void kernel_main(multiboot_info_t* mbt, unsigned int magic) 
{
	//store multiboot header globally
	bootHeader = mbt;
	terminalInitialize();
//	printGrubMemoryMap();
	heapInit();
	printFreeList();
	void* ptr1 = getHeapMemory(20);
	printFreeList();
	void* ptr2 = getHeapMemory(30);
	printFreeList();
	freeHeapMemory(ptr1);
	printFreeList();
	freeHeapMemory(ptr2);
	printFreeList();
	
	//memoryInitialize();
}
