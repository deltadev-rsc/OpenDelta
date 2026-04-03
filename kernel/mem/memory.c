#include "../lib/string.h"

void append(char s[], char n)
{
	int len = strlen(s);
	s[len] = n;
	s[len+1] = '\0';
}

void backspace(char s[])
{
	int len = strlen(s);
	s[len-1] = '\0';
}

void flush(char *var) 
{
	int i = 0;
	while(var[i] != '\0')  {
		var[i] = '\0';
		i++;
	}
}

void *memcpy(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;
	
	for(size_t i = 0; i < n; i++) {
		d[i] = s[i];
	}
	return dest;
}

void *memset(void *str, int c, size_t n)
{
	char *s = str;

	for(size_t i = 0; i < n; i++) {
		*(s + i) = c;
	}

	return str;
}

void memory_copy(unsigned char *source, unsigned char *dest, int nbytes) 
{
	int i;
	for (i = 0; i < nbytes; i++)  {
		*(dest + i) = *(source + i);
	}
}

void memory_set(uint8_t *dest, uint8_t val, uint32_t len)
{
	uint8_t *temp = (uint8_t *)dest;
	for( ; len != 0; len--) {
		 *temp++ = val;
	}
}


