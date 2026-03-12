#include "../types.h"

typedef enum {
    WHITE = 0x0F,
    BLACK = 0x0,
    CYAN = 0x3,
    DGRAY = 0x8,   // Dark Gray
    LCYAN = 0xB,   // Light Cyan
    LGRAY = 0x7    // Light Gray
} Colors;


void outb(uint16_t port, uint8_t val) {
    __asm__ __volatile__ ("outb %0, %1" : : "a" (val), "Nd" (port));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (ret) : "Nd" (port));
    return ret;
}

void prints(const char *str, Colors color)
{
    char *video_mem = (char *)0xb8000;
    int i = 0;
    int pos = 0;
    while (str[i] != '\0') {

        if (str[i] == '\n') {
            pos = ((pos / 80) + 1) * 80;
        }

        else {
            video_mem[2*pos] = str[i];
            video_mem[2*pos + 1] = (char)color;
            pos++;
        }

        i++;
    }
}
