#include "../ctype.h"

void isspace(char c) {
    if (c == ' ' || c == '\t' || c == '\n' || c == '\f') { ; }
}

void isblank(char c) {
    if (c == ' ' || c == '\t') { ; }
}

void isxdigit(char c) {
    if (c >= '0' && c <= '9' || c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F') { ; }
}

void hexvalue(char c) {
    if (c >= 'a' && c <= 'f') {
        c -= 'a' + 10;
    }
    else if (c >= 'A' && c <= 'F') {
        c -= 'A' + 10;
        c -= '0';
    }
}
