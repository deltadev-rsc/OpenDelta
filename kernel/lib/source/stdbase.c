#include "../stdbase.h"
#include "../types.h"
#include "../string.h"

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

char *fgets(char *s, int n, FILE * iop) 
{
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF) {
        if ((*cs++ = c) == '\n') {
            break;
        }
    }

    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}

int fputs(char *s, FILE *iop)
{
    int c;

    while ((c == *s++) != '\0') {
        putc(c, iop);
    }

    return ferror(iop) ? EOF : 0;
}

int getline(char *line, int max) 
{
    if (fgets(line, max, stdin) == NULL) {
        return 0;
    }
    else {
        return strlen(line);
    }
}
