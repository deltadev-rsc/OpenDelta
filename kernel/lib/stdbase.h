#ifndef BASE_H
#define BASE_H

#include "./types.h"

#define ALIGN 8
#define MAGIC 0xB16B00B5U

/* colors */
typedef enum {
    WHITE = 0x0F,
    BLACK = 0x0,
    CYAN = 0x3,
    DGRAY = 0x8,   // Dark Gray
    LCYAN = 0xB,   // Light Cyan
    LGRAY = 0x7    // Light Gray
} Colors;

typedef struct {
    uint32_t magic;
    size_t size;
    int free;
    struct block_header *prev;
    struct block_header *next;
} block_header_t;

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;

/* input-output */
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);
void prints(const char *str, unsigned int color);
void kprint(const char *str, unsigned int color);
void kprintnl(void);

#endif
