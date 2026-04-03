#ifndef STRING_H
#define STRING_H

#include "types.h"

#define size_t	unsigned long int

int strindex(char s[], char t[]);

int strcmp(const char *stra, const char *strb);
int strncmp(const char *cs, const char *ct, size_t n); 

size_t strlen(const char *str);
size_t strnlen(const char *s, size_t maxlen);

char *strcat(char *dest, const char *src);

char *s_strncpy(char *s1, const char *s2, size_t n);

void int_to_ascii(int n, char str[]);

void hex_to_ascii(int n, char str[]);

int sprintf(char *buf, const char *fmt);

void *s_malloc(unsigned int size);

uint32_t kmalloc(size_t size, int align, uint32_t *phys_addr);

#endif
