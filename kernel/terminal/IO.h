#ifndef IO_H
#define IO_H
#include <stddef.h>
#include <stdint.h>
#include "scancodes.h"

inline uint8_t inb(uint16_t port){
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

inline void outb(uint16_t port, uint8_t val){
	asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static char getScancode(){
    while(!(inb(0x64) & 1));
	int code = inb(0x60);
	if(code == 224)
		code = inb(0x60);
    return kbdus[code];
}

#endif
