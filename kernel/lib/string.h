#ifndef STRING_H
#define STRING_H

#include "types.h"

#define size_t	unsigned long int

int strindex(char s[], char t[]);

int strcmp(const char *stra, const char *strb);
int strncmp(const char *cs, const char *ct, unsigned int n); 

unsigned int strlen(const char *str);
unsigned int strnlen(const char *str, unsigned int maxlen);

char *strcat(char *dest, const char *src);

char *strncpy(char *s1, const char *s2, unsigned int n);

void int_to_ascii(int n, char str[]);

void hex_to_ascii(int n, char str[]);

int sprintf(char *buf, const char *fmt);

#endif
