#include "../types.h"

uint64_t next = 1;

int rand(void)
{
    next = next * 1103515245 + 12345;
    return (uint32_t) (next / 65536) % 32768;
}

void srand(uint32_t seed) 
{
    next = seed;
}

void squeeze(char s[], int c) 
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++) {
        if (s[i] != c) {
            s[j] = s[i];
            j++;
        }
    }

    s[j] = '\0';
}

unsigned getbits(unsigned x, int p, int n) {
    return (x >> (p+1-n)) & ~ (~0 << n);
} 
