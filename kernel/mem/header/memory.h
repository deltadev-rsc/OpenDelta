#ifndef MEMORY_H
#define MEMORY_H

#include "../../lib/types.h"
#include "../../lib/system.h"

void append(char s[], char n);
void backspace(char s[]);
void flush(char *var);

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *str, int c, size_t n);
void memmory_copy(unsigned char *source, unsigned char *dest, int nbytes);
void memory_set(uint8_t *dest, uint8_t val, uint32_t len);

void paggingInstall(uint32_t memsize);
void heapInstall(void);
void switchPageDir(page_dir_t *dir);

#endif 
