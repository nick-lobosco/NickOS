#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>
#include "../multiboot.h"

#define MB 1000000
#define MINHEAPSTART 100*MB
#define MAXHEAPLENGTH 100*MB

/* Heap Struct Definitions */
typedef struct heapBlock{
	uint32_t length;
}heapBlock;

typedef struct freeHeapBlock freeHeapBlock;
struct freeHeapBlock{
	uint32_t length;
	freeHeapBlock* prev;
	freeHeapBlock* next;
};

/* Heap Global Variables */
freeHeapBlock* freeList;
uint32_t heapLength;

/* Heap Functions */
void printGrubMemoryMap();
void heapInit();
void* getHeapMemory(size_t size);
void freeHeapMemory(void* ptr);
void printFreeList();


#endif
