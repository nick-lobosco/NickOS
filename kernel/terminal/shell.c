#include "shell.h"
#include "terminal.h"
#include "IO.h"
#include "../memory/memory.h"
#include "../libc/string.h"
#include "../libc/stdio.h"

void updateCursor(uint16_t pos){
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
	return;
}

void cursorLeft(){
	if(cursorIndex > cmdStart)
		updateCursor(--cursorIndex);
	return;
}

void cursorRight(){
	if(cursorIndex < cmdEnd)
		updateCursor(++cursorIndex);
	return;
}

void runShell(){
	if(!terminalInitialized)
		terminalInitialize();
	else
		clearTerminal();
	shellRunning = 1;
	terminalBuffer[0] = vgaEntry('$', terminalColor);
	cursorIndex = 1;
	updateCursor(cursorIndex);
	cmdStart = 1;
	cmdEnd = 1;
	while(shellRunning);
}

void delete(){
	if(cursorIndex == cmdEnd)
		return;
	uint32_t i;
	for(i=cursorIndex; i<cmdEnd; i++)
		terminalBuffer[i] = terminalBuffer[i+1];
	cmdEnd--;
	return;
}

void backspace(){
	if(cursorIndex==cmdStart)
		return;
	uint32_t i;
	for(i=cursorIndex-1;i<cmdEnd; i++)
		terminalBuffer[i] = terminalBuffer[i+1];
	cursorLeft();
	cmdEnd--;
	return;
}
void shellPutChar(char c){
	uint32_t i;
	for(i=++cmdEnd; i>cursorIndex; i--){
		terminalBuffer[i] = terminalBuffer[i-1];
	}
	if(shiftHeld && isLower(c)){
		c = 'A' + (c - 'a');
	}
	terminalBuffer[cursorIndex++] = vgaEntry(c, terminalColor);
	updateCursor(cursorIndex);
	return;
}

void shellHelp(){
	printf("Valid commands:\n");
	printf("printgrub\nprintfreelist\nclear\n");
}

void handleShellCommand(){
	terminalIndex = VGA_WIDTH*((cursorIndex/VGA_WIDTH)+1);
	cursorIndex = terminalIndex;
	printf("%d\n",cmdEnd-cmdStart+1);
	char* tempStr = getHeapMemory(cmdEnd-cmdStart+1);
	int i;
	for(i=0; i<cmdEnd-cmdStart; i++)
		tempStr[i] = (terminalBuffer[cmdStart+i]&0xFF);
	tempStr[i] = 0;
	//printf("%s\n", tempStr);
	int p = 0;
	if(strcmp(tempStr, "help") == 0){
		shellHelp();
	}
	else if(strcmp(tempStr, "printgrub")==0)
		printGrubMemoryMap();
	else if(strcmp(tempStr, "printfreelist")==0)
		p = 1;
	else if(strcmp(tempStr, "clear")==0)
		clearTerminal();	
	else{
		printf("Invalid Command: use command 'help' to see valid commands\n");
	}
	freeHeapMemory(tempStr);
	if(p==1)
		printFreeList();
	cursorIndex = terminalIndex;
	cmdStart = cursorIndex + 1;
	cmdEnd = cursorIndex;
	shellPutChar('$');
	return;
}

void handleKeyPress(){
	int code = inb(0x60); //get input char
	outb(0x20,0x20); //acknowledge keypress
	//printf("%d\n", code);
	if(code == 42 || code == 54){ //shift pressed
		shiftHeld++;
		return;
	}
	if(code == 170 || code == 182){ //shift released
		shiftHeld--;
		return;
	}
	if(code > 0x58)
		return;	
	char c = kbdus[code];
	switch(c){
		case 0:
			break;
		case '\n':
			handleShellCommand();
			break;
		case 17:
			cursorLeft();
			break;
		case 18:
			cursorRight();
			break;
		case 127:
			delete();
			break;
		case '\b':
			backspace();
			break;
		default:
			shellPutChar(c);
			break;
	} 
}


