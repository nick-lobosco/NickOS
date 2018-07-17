#include <stdarg.h>
#include "string.h"
#include "stdio.h"
#include "../terminal/terminal.h"

int printf(const char* format, ...){
	//vars since apparently defining vars in a switch is a no-no
	int intVar;
	char charVar;
	char* stringVar;
	unsigned int uintVar;

	int written=0;	
	va_list args;
	va_start(args, format);
	int len = strlen(format);
	int i;
	for(i=0;i<len;i++){
		if(format[i] == '%'){
			i++;
			switch(format[i]){
				case 'd':
				case 'i':
					intVar = va_arg(args, int);
					terminalWriteInt(intVar, 10);
					break;
				case 'c':
					charVar = va_arg(args, int);
					terminalPutchar(charVar);	
					break;
				case 's':
					stringVar = va_arg(args, char*);
					terminalWriteString(stringVar);
					break;
				case 'u':
					uintVar = va_arg(args, unsigned int);
					terminalWrite_uint(uintVar);
					break;
				case 'l':
				case 'b':
					intVar = va_arg(args, int);
					terminalWriteInt(intVar, 2);
					break;
				case 'x':
					intVar = va_arg(args, int);
					terminalWriteInt(intVar, 16);
					break;
				case 'o':
					intVar = va_arg(args, int);
					terminalWriteInt(intVar, 8);
					break;
				case '%':
					terminalPutchar('%');
					break;	
			}
		}
		else{
			terminalPutchar(format[i]);			
		}
	}	
	return written;
}
