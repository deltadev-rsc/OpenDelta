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
