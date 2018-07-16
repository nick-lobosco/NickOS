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
					terminalWrite_uint(intVar);
					break;
				case 'c':
					charVar = va_arg(args, int);
					terminalPutchar(charVar);	
					break;
				case 's':
					stringVar = va_arg(args, char*);
					terminalWrite_string(stringVar);
					break;
				case 'u':
					uintVar = va_arg(args, unsigned int);
					terminalWrite_uint(uintVar);
					break;
				case 'l':
				case 'b':
				case 'x':
				case 'o':
				case '%':
					break;	
			}
		}
		else{
			terminalPutchar(format[i]);			
		}
	}	
	return written;
}
