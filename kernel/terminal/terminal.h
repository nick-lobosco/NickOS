#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <stddef.h>
#include "../libc/string.h"

/* Hardware text mode color constants. */
enum vgaColor {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
 
inline uint8_t vgaEntryColor(enum vgaColor fg, enum vgaColor bg) 
{
	return fg | bg << 4;
}
 
inline uint16_t vgaEntry(unsigned char uc, uint8_t color){
	return (uint16_t) uc | (uint16_t) color << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
uint8_t terminalInitialized;

uint16_t terminalIndex;
uint8_t terminalColor;
uint16_t cursorIndex;
uint16_t cmdStart;
uint16_t cmdEnd;
volatile uint16_t* terminalBuffer;

void terminalInitialize(void); 
void terminalSetcolor(uint8_t color); 
void terminalPutchar(char c); 
void terminalWrite(const char* data, size_t size); 
void clearTerminal();

void terminalWriteInt(int x, int base);
void terminalWriteString(const char* data); 
void terminalWrite_uint(unsigned int x);
/*
void terminalWriteAddress(unsigned long long x);
void cursorLeft();
void cursorRight();
void del();
void back();
void updateCursor(uint16_t pos);
*/
#endif
