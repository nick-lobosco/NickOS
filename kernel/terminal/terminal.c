#include "terminal.h"
#include "IO.h"
#include "../libc/Math.h"

void terminalInitialize(void) 
{
	terminalColor = vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminalBuffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminalBuffer[index] = vgaEntry(' ', terminalColor);
		}
	}
	index=0;
}

void terminalSetcolor(uint8_t color) 
{
	terminalColor = color;
}
 
void terminalPutchar(char c) 
{
	if (c == '\n'){
		index=VGA_WIDTH*((index/VGA_WIDTH)+1);
	}
	else{
		terminalBuffer[index++]=vgaEntry(c, terminalColor);
	}
}
 
void terminalWrite(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminalPutchar(data[i]);
}

void terminalWrite_string(const char* data){
	terminalWrite(data, strlen(data));
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

/*

void terminalInitialize(void) 
{
	terminalColor = vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminalBuffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminalBuffer[index] = vgaEntry(' ', terminalColor);
		}
	}
	int index=0;
	currentStart = 1;
	currentEnd = 1;
	terminalBuffer[0] = vgaEntry('$', terminalColor);
	cursorIndex = 1;
	updateCursor(1);
}
void terminalWriteAddress(unsigned long long x){
	if(x==0){
		terminalPutchar(48);
		return;
	}
	unsigned long long i;
	short digit;
	char set = 0;
	for(i=(unsigned long long)10000000000000000000;i>0;i=i/10){
		digit = (x/i)%10;
		if(!set && digit)
			set = 1;
		if(set) 
			terminalPutchar(48+digit);
	}
}

void cursorLeft(){
	if(cursorIndex > currentStart)
		updateCursor(--cursorIndex);
}

void cursorRight(){
	if(cursorIndex < currentEnd)
		updateCursor(++cursorIndex);
}

void del(){
	if(cursorIndex==currentEnd)
		return;
	int i;
	for(i=cursorIndex; i<currentEnd; i++){
		terminalBuffer[i] = terminalBuffer[i+1];
	}	
	//terminal_buffer[currentEnd] = vga_entry(' ', terminal_color);
	if(cursorIndex == currentEnd)
		updateCursor(--cursorIndex);
	currentEnd--;
}

void back(){
	if(cursorIndex==currentStart)
		return;
	int i;
	for(i=cursorIndex-1; i<currentEnd; i++){
		terminalBuffer[i] = terminalBuffer[i+1];
	}	
	updateCursor(--cursorIndex);
	currentEnd--;
}

void getInput(){
    char c = 0;
    while (1){
        c = getScancode();
        getScancode(); //ignore release code
		if(c==17)
			cursorLeft();
		else if(c==18)
			cursorRight();
		else if(c==127)
			del();
		else if(c=='\b')
			back();
        else if(!c)
            continue;
		else
        	terminalPutchar(c);
    }
}

void terminalPutchar(char c) 
{
	if (c == '\n'){
		index=VGA_WIDTH*((index%VGA_WIDTH)+1);
	}
	else{
		termincalBuffer[index++]=c;
	}
		if(currentStart!=currentEnd){

			int outputIndex = cursorIndex + (VGA_WIDTH - currentEnd%VGA_WIDTH);
			int outputLen = currentEnd - currentStart;
			int i;
			for(i=0;i<outputLen;i++){
				terminalBuffer[outputIndex++] = terminalBuffer[currentStart+i];
			}
			cursorIndex = outputIndex + (VGA_WIDTH - outputIndex%VGA_WIDTH);	
		}
		else{
			cursorIndex += VGA_WIDTH-1;
		}	
		terminalBuffer[cursorIndex++] = vgaEntry('$', terminalColor);
		currentStart = cursorIndex;
		currentEnd = currentStart; 
	}
	else{
		int i;
		for(i=currentEnd; i>cursorIndex; i--){
			terminalBuffer[i] = terminalBuffer[i-1];
		}
		terminalBuffer[cursorIndex++] = vgaEntry(c, terminalColor);
		currentEnd++;
	}	
	updateCursor(cursorIndex);
}
 
void updateCursor(uint16_t pos){
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));

}


*/ 
