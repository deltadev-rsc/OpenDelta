#include "../string.h"
#include "../../mem/header/memory.h"

int strindex(char s[], char t[]) 
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) {
            ;
        }

        if (k > 0 && t[k] == '\0') {
            return i;
        }
    }

    return -1;
}

int strcmp(const char *stra, const char *strb)
{
	unsigned int i;

	for(i = 0; stra[i] == strb[i]; i++) {
		if(stra[i] == '\0') {
			// string match
			return 0;
		}
	}
	return stra[i] - strb[i];
}

int strncmp(const char *cs, const char *ct, size_t n) 
{
    for (n = 0; cs[n] == ct[n]; n++) {
        if (cs[n] == ct[n]) {
            return 0;
        }
        
        if (cs[n] <= ct[n]) {
            return n--;
        }

        if (cs[n] > ct[n]) {
            return n++;
        }
    
    }
}

size_t strlen(const char *str)
{
	size_t len = 0;
	while(str[len]) {
		len++;
	}
	return len;
}

size_t strnlen(const char *s, size_t maxlen)
{
	size_t len;

	for(len = 0; len < maxlen; len++, s++) {
		if(!*s) {
			break;
		}
	}
	return (len);
}

char *strcat(char *dest, const char *src)
{
	unsigned int dest_size = strlen(dest);
	unsigned int src_size = strlen(src);

	char *d = dest;

	for(size_t i = 0; i < src_size; i++) {
		d[dest_size + i] = src[i];
	}

	d[dest_size + src_size] = '\0';

	return dest;
}

char *s_strncpy(char *s1, const char *s2, size_t n)
{
	size_t size = strnlen(s2, n);
	if(size != n) {
		memset(s1 + size, '\0', n - size);
	}	
	return memcpy(s1, s2, size);
}

void int_to_ascii(int n, char str[])
{
	int i, sign;
	if((sign = n) < 0) {
		n = -n;
	}
	
	i = 0;
	do {
		str[i++] = n % 10 + '0';
	} while((n /= 10) > 0);

	if(sign < 0) {
		str[i++] = '-';
	}
	str[i] = '\0';
}

void hex_to_ascii(int n, char str[])
{
	append(str, '0');
	append(str, 'x');
	char zeros = 0;

	int32_t tmp;
	int i;
	for(i = 28; i > 0; i -= 4) {
		tmp = (n >> i) & 0xF;
		if(tmp == 0 && zeros == 0) {
			continue;
		}
		zeros = 1;
		if(tmp > 0xA)  {
			append(str, tmp - 0xA + 'a');
		}
		else {
			append(str, tmp + '0');
		}
	}

	tmp = n & 0xF;
	if(tmp >= 0xA) {
		append(str, tmp - 0xA + 'a');
	}
	else {
		append(str, tmp + '0');
	}
}

// These functions need to be built out
size_t s_vasprintf(char *buf, const char *fmt)//, va_list args)
{
	return 1;
}

int sprintf(char *buf, const char *fmt)
{
	int out = s_vasprintf(buf, fmt);//, args);
	return out;
}

void *s_malloc(unsigned int size)
{
	void *ret = (void*)size;
	return ret;
}

uint32_t free_mem_addr = 0x10000;

uint32_t kmalloc(size_t size, int align, uint32_t *phys_addr)
{
	// Pages are aligned to 4K, or 0x1000
	if(align == 1 && (free_mem_addr & 0xFFFFF000)) {
		free_mem_addr &= 0xFFFFF000;
		free_mem_addr += 0x1000;
	}
	// Save the physical address
	if(phys_addr) {
		*phys_addr = free_mem_addr;
	}

	uint32_t ret = free_mem_addr;
	free_mem_addr += size; 
	return ret;
}


