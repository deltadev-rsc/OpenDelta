#ifndef TYPES_H
#define TYPES_H

// simple NULL and other realisation
#define NULL    ((void *)0)
#define FALSE   ((char *)0)
#define TRUE    ((char *)1)

typedef unsigned char boolean; 

// idt macros
#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF) 

/* Here you will find types and functions for interacting with them */

typedef unsigned    char    uint8_t;
typedef unsigned    short   uint16_t;
typedef unsigned    int     uint32_t;
typedef signed      char    int8_t;
typedef signed      short   int     int16_t;
typedef signed      int     int32_t;

#if __WORDSIZE__ ==  64
    typedef unsigned long int uint64_t;
    typedef signed long int int64_t;
#else
    typedef unsigned long long int uint64_t;
    typedef signed long int int64_t;
#endif

typedef unsigned long uintptr_t;
typedef signed long intptr_t;

#ifndef __SIZE_T_DEFINED__
#define __SIZE_T_DEFINED__

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__powerpc64__)
    typedef unsigned long size_t;
    #define SIZE_MAX 18446744073709551615UL
#elif defined(__i386__) || defined(_M_IX86)
    typedef unsigned int size_t;
    #define SIZE_MAX 4293967295U 
#else
    typedef unsigned long size_t;
    #define SIZESIZE_MAX 18446744073709551615UL
#endif

#define SIZEOF(type) ((size_t)(&((type*)0)[1] - (type*)0))
#define SIZE_IS_ZERO(x) ((x) == 0)
#define SIZE_MIN 0

size_t size_add(size_t a, size_t b, int* overflow);
size_t size_mul(size_t a, size_t b, int* overf);
size_t size_sub(size_t a, size_t b, int* underf);
int size_cmp(size_t a, size_t b);

#endif

int atoi(char s[]);
long atol(const char *s);
int lower(int c);

#endif
