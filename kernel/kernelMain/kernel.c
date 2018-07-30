#include "../multiboot.h"
#include "../libc/stdio.h"
#include "../terminal/terminal.h"
#include <stdint.h> 
#include "tables.h"
#include "kernel.h"
#include "../memory/memory.h"
#include "../terminal/shell.h"

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)

#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif


void kernel_main(multiboot_info_t* mbt, unsigned int magic) 
{
	//store multiboot header globally
	bootHeader = mbt;
	terminalInitialized = 0;
	shellRunning = 0;
	heapInitialized = 0;

	runShell();
/*
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
*/
}
