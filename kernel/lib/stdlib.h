/* вспомогательые функции */
#ifndef STDLIB_H
#define STDLIB_H

#include "./types.h"

/* переменные для использования вне функций */
uint64_t next = 1;

int rand(void);
void srand(uint32_t seed);

void squeeze(char s[], int c);

unsigned getbits(unsigned x, int p, int n);

#endif
