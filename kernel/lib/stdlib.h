/* вспомогательые функции */
#ifndef STDLIB_H
#define STDLIB_H

#include "./types.h"

/* переменные для использования вне функций */
uint64_t next = 1;

int rand(void);
void srand(uint32_t seed);

int power(int base, int n);
int trim(char s[]);

void copy(char st[], char sf[]);
void shellSort(int v[], int n);
void squeeze(char s[], int c);
void reverse(char s[]);

int bitcount(unsigned x);
int binsearch(int x, int v[], int n);
unsigned getbits(unsigned x, int p, int n);

#endif
