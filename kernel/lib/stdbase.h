#ifndef BASE_H
#define BASE_H

#include "./types.h"

#define ALIGN 8
#define MAGIC 0xB16B00B5U

/*---for-screen-driver---*/
#define LINES 				25
#define COLUMNS_IN_LINE 		80
#define BYTES_FOR_EACH_ELEMENT 		2
#define SCREENSIZE 			BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

#define KEYBOARD_DATA_PORT 		0x60
#define KEYBOARD_STATUS_PORT 		0x64
#define IDT_SIZE 			256
#define INTERRUPT_GATE 			0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 	0x08

#define ENTER_KEY_CODE 			0x1C
#define ENTER_BACKSPACE_CODE		0x0E

#define REG_SCREEN_CTRL			0x3d4
#define REG_SCREEN_DATA			0x3d5

static unsigned int currentLoc = 0;
static char *vidptr = (char*)0xb8000;

/* colors */
typedef enum {
    WHITE = 0x0F,
    BLACK = 0x0,
    CYAN = 0x3,
    DGRAY = 0x8,   // Dark Gray
    LCYAN = 0xB,   // Light Cyan
    LGRAY = 0x7    // Light Gray
} Colors;

/*---structures-for-system---*/
typedef struct {
    uint32_t magic;
    size_t size;
    int free;
    struct block_header *prev;
    struct block_header *next;
} block_header_t;

struct IDTEntry {
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

/*---For-Base---*/

#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
            ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x,p) (--(p)->cnt >= 0 \
            ? * (p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)


typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} FILE;

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
extern FILE _iob[OPEN_MAX];

enum _flags {
    _READ = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF = 010,
    _ERR = 020
};

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
static unsigned int curret_loc = 0;

char *fgets(char *s, int n, FILE * iop);
int fputs(char *s, FILE *iop);
int getline(char *line, int max);

/* input-output */
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);
void prints(const char *str, unsigned int color);
void kprint(const char *str, unsigned int color);
void kprintnl(void);

#endif
