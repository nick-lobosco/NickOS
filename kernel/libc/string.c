#include <stddef.h>
#include "string.h"

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int strcmp(char* str1, char* str2){
	while(*str1 && *str2){
		if(str1[0] != str2[0])
			return 1;
		str1++;
		str2++;
	}
	if(*str1 || *str2)
		return 1;
	return 0;		
}
