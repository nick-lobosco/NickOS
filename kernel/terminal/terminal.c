#include "terminal.h"
#include "IO.h"
#include "../libc/Math.h"


void clearTerminal(){
	size_t index;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			index = y * VGA_WIDTH + x;
			terminalBuffer[index] = vgaEntry(' ', terminalColor);
		}
	}
}

void terminalInitialize(void) 
{
	terminalInitialized = 1;
	terminalColor = vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminalBuffer = (uint16_t*) 0xB8000;
	clearTerminal();
	terminalIndex=0;
}

void terminalSetcolor(uint8_t color) 
{
	terminalColor = color;
}
 
void terminalPutchar(char c) 
{
	if (c == '\n'){
		terminalIndex=VGA_WIDTH*((terminalIndex/VGA_WIDTH)+1);
	}
	else{
		terminalBuffer[terminalIndex++]=vgaEntry(c, terminalColor);
	}
}
 
void terminalWrite(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminalPutchar(data[i]);
}

void terminalWriteString(const char* data){
	terminalWrite(data, strlen(data));
}
 
char getChar(int x){
	if(x<10)
		return '0' + x;
	return 'A' + x - 10;
}

void terminalWriteInt(int x, int base){
	int maxSize;
	int neg=0;
	char num[32]; 
	if(x==0){
		terminalPutchar('0');
		return;
	}
	else if(x<0){
		neg=1;
		x*=-1;
	}
	switch(base){
		case 10:
			maxSize=10;
			break;
		case 2:
			maxSize=32;
			break;
		case 8:
			maxSize=11;
			break;
		case 16:
			maxSize=8;
			break;
		default:
			return;
	}
		
	int i, digit, div;
	int len=0;
	for(i=0;i<maxSize;i++){
		div = i ? pow(base,i) : 1;
		digit = (x/div)%base;
		if(digit)
			len=i+1;
		num[maxSize -1 -i] = getChar(digit);
	}
	if(neg)
		terminalPutchar('-');
	if(base==16)
		terminalWriteString("0x");
	for(i=maxSize-len;i<maxSize;i++){
		terminalPutchar(num[i]);
	}
}



void terminalWrite_uint(unsigned int x){
	if(x==0){
		terminalPutchar(48);
		return;
	}
	const int MAXINTSIZE=10;
	char num[MAXINTSIZE]; 
	int i, digit, div;
	int len=0;
	for(i=0;i<10;i++){
		div = i ? pow(10,i) : 1;
		digit = (x/div)%10;
		if(digit)
			len=i+1;
		num[9-i] = '0' + digit;
	}
	for(i=MAXINTSIZE-len;i<MAXINTSIZE;i++){
		terminalPutchar(num[i]);
	}
}

