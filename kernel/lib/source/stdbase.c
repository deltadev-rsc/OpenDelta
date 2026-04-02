#include "../stdbase.h"
#include "../types.h"
#include "../string.h"

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
extern FILE _iob[OPEN_MAX];

static Header base;
static Header *freep = NULL;

static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC) {
        nu = NALLOC;
    }

    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) - 1) {
        return NULL;
    }
    up = (Header *) cp;
    up->s.size = nu;
    free((void *) (up + 1));
    return freep;
}

void *free(void *ap)
{
    Header *bp, *p;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            break;
        }
    }

    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else {
        bp->s.ptr = p->s.ptr;
    }

    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else {
        p->s.ptr = bp;
    }

    freep = p;
}

void *malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits) {
                prevp->s.ptr = p->s.ptr;
            }
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }

        if (p == freep) {
            if ((p = morecore(nunits)) == NULL) {
                return NULL;
            }
        }
    }
}

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

int _getc(FILE *stream)
{
    if (--(stream)->cnt >= 0) {
        (unsigned char) *(stream)->ptr ; _fillbuf(stream);
    }
}

int _putc(int c, FILE *stream) 
{
    if (--(stream)->cnt >= 0) {
        *(stream)->ptr++ = (c) ; _flushbuf((c), stream);
    }
}

char *fgets(char *s, int n, FILE * iop) 
{
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = _getc(iop)) != EOF) {
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
        _putc(c, iop);
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
