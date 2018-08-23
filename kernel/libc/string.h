#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t strlen(const char* str);
int strcmp(char* str1, char* str2);
int isAlpha(char c);
int isUpper(char c);
int isLower(char c);

#endif
