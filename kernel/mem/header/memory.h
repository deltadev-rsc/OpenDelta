#ifndef MEMORY_H
#define MEMORY_H

#pragma once

#include "../../lib/types.h"
#include "../../lib/system.h"

#ifdef __cplusplus
extern "C" {
#endif 

void append(char s[], char n);
void backspace(char s[]);
void flush(char *var);

int memcmp(const void* ptr1, const void* ptr2, uint16_t num);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *str, int c, size_t n);
void memmoryCopy(unsigned char *source, unsigned char *dest, int nbytes);
void memorySet(uint8_t *dest, uint8_t val, uint32_t len);

void paggingInstall(uint32_t memsize);
void heapInstall(void);
void switchPageDir(page_dir_t *dir);

#ifdef __cplusplus 
}
#endif

#endif 
