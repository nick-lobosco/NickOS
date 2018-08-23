#include "memory.h"
#include "../kernelMain/kernel.h"
#include "../libc/stdio.h"
#include "../libc/Math.h"

void printGrubMemoryMap(){
    multiboot_memory_map_t *map = (multiboot_memory_map_t*)bootHeader->mmap_addr;
	uint32_t i;
	for(i=0;i<bootHeader->mmap_length;i+=map->size+4){
		map=(multiboot_memory_map_t*)(bootHeader->mmap_addr+i);
		printf("size: %d   addr_low: %u   addr_high: %u   len_low: %u   len_high: %u   type: %d\n",
			map->size, map->addr_low, map->addr_high, map->len_low, map->len_high, map->type);
	}
}

void printFreeList(){
	freeHeapBlock* ptr = freeList;
	while(ptr){
		printf("addr: %u, length: %u, use: %u, prev: %u, next: %u\n",ptr, ptr->length, ptr->length&1, ptr->prev, ptr->next);
		ptr=ptr->next;
	}	
}

void heapInit(){
	if(heapInitialized)
		return;
	heapInitialized = 1;
	/* heap global variable initializations */
	freeList = NULL;
	
	/* heap temp variables */
	freeHeapBlock *prevFreeBlock = NULL;
	freeHeapBlock *header;
	heapBlock *footer;
	uint32_t remainingHeapLength = MAXHEAPLENGTH;
	uint32_t blockLength;
	
	/* memory map traversal variables */
	multiboot_memory_map_t* mapEntry;
	uint32_t mapLength = bootHeader->mmap_length;	
	
	/* Traverse memory map and create free list up to 100 MB */
	uint32_t i, start;
	for(i=0; i<mapLength && remainingHeapLength>0; i+=mapEntry->size+4){
		mapEntry=bootHeader->mmap_addr+i;
		if(mapEntry->type == 1){ //usable memory
			if(mapEntry->addr_low + mapEntry->len_low < MINHEAPSTART) //reserved memory
				continue;
			start = (mapEntry->addr_low<MINHEAPSTART ? MINHEAPSTART : mapEntry->addr_low);
			blockLength = min(remainingHeapLength, mapEntry->addr_low + mapEntry->len_low - start);
			blockLength -= blockLength%2; //make even
			if(blockLength < sizeof(heapBlock) + sizeof(freeHeapBlock)) //block too small
				continue;
			if(freeList == NULL) //first free block
				freeList = (freeHeapBlock*)start;
			else //prevFreeBlock initialized
				prevFreeBlock->next = (freeHeapBlock*)start;
			header = (freeHeapBlock*)start;
			header->length = blockLength - 2*sizeof(heapBlock);
			header->prev = prevFreeBlock;
			header->next = NULL;
			footer = (heapBlock*)(start + blockLength - 2*sizeof(heapBlock));
			footer->length = header->length;
			prevFreeBlock = header;
			remainingHeapLength -= blockLength;
		}
	}
	heapLength = MAXHEAPLENGTH - remainingHeapLength;
}

void* getHeapMemory(size_t size){
	if(size<8)
		size=8;
	if(!heapInitialized)
		heapInit();
	size += size%2; //make even
	freeHeapBlock* freePtr = freeList;
	void* data;
	while(freePtr){
		data = (uint8_t*)freePtr+sizeof(heapBlock);
		if(freePtr->length >= size + sizeof(freeHeapBlock) + sizeof(heapBlock)){ //split block in two
				uint32_t length1 = size;
				uint32_t length2 = freePtr->length -2* sizeof(heapBlock) - size;
				heapBlock* header1 = (heapBlock*)freePtr;
				heapBlock* footer1 = (uint8_t*)freePtr + sizeof(heapBlock) + length1;
				freeHeapBlock* header2 = (uint8_t*)footer1 + sizeof(heapBlock);
				heapBlock* footer2 = (uint8_t*)header2 + sizeof(heapBlock) + length2;
				header1->length = length1 + 1;
				footer1->length = header1->length;
				header2->length = length2;
				footer2->length - header2->length;
				if (freePtr->prev)
					freePtr->prev->next = header2;
				else
					freeList = header2;
				if(freePtr->next)
					freePtr->next->prev = header2;
				header2->prev = freePtr->prev;
				header2->next = freePtr->next;
				return data;
		}
		else if(freePtr->length >= size){ //return whole block
				heapBlock* header = (heapBlock*)freePtr;
				heapBlock* footer = (uint8_t*)freePtr + sizeof(heapBlock) + header->length;
				header->length += 1;
				footer->length += 1;
				if(freePtr->prev)
					freePtr->prev->next = freePtr->next;
				else
					freeList = freePtr->next;
				if(freePtr->next)
					freePtr->next->prev = freePtr->prev;
				return data;
		}
		else //block too small
			freePtr = freePtr->next; 
	}
	return NULL;
}

void freeHeapMemory(void* ptr){
	freeHeapBlock* header = (freeHeapBlock*)((uint8_t*)ptr - sizeof(heapBlock));
	header->length -=1;
	heapBlock* footer = (heapBlock*)((uint8_t*)ptr + header->length);
	footer->length-=1;
	freeList->prev = header;
	header->prev = NULL;
	header->next = freeList;
//	printf("len: %d, prev %u, next %u\n", header->length, header->prev, header->next);
	freeList = header;
}

