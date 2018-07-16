#ifndef IO_H
#define IO_H
#include <stddef.h>
#include <stdint.h>

static unsigned char kbdus[128] = 
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    19,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    17,	/* Left Arrow */
    0,
    18,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    20,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    127,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

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

static char gs(){
	int code = inb(0x60);
	if(code <= 0x58)
    	return kbdus[code];
	else
		return -1;
}
#endif
