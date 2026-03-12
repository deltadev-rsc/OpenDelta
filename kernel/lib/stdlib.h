/* вспомогательые функции */
#ifndef STDLIB_H
#define STDLIB_H

#include "./types.h"

/* переменные для использования вне функций */
uint64_t next = 1;

int rand(void);
void srand(uint32_t seed);

#endif
