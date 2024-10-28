#include "common.h"

size_t itos(s64 num, char *str) {
    if (num == 0) {
        *str++ = '0';
        *str = 0;
        return 1;
    }

    char buf[32];
    size_t idx = 0;

    if (num < 0) {
        buf[idx++] = '-';
    }

    while (num) {
        buf[idx++] = num % 10 + 0x30;
        num /= 10;
    }

    size_t size = idx;
        
    while (idx > 0) {
        *str++ = buf[--idx];
    }

    *str = '\0';
    return size;
}

size_t i16tos(u64 num, char *str) {
    char hex_digits[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    char buf[32];
    size_t idx = 0;
    size_t size = 0;

    if (num == 0) {
        buf[idx++] = '0';
        buf[idx++] = 'x';
        buf[idx++] = '0';
        goto REVERSE;
    }

    while (num) {
        buf[idx++] = hex_digits[num % 16];
        num /= 16;
    }

    buf[idx++] = 'x';
    buf[idx++] = '0';
        
REVERSE:
    size = idx;
    while (idx > 0) {
        *str++ = buf[--idx];
    }

    *str = '\0';
    return size;
}

s32 isdigit(s32 c) {
    return (c >= '0' && c <= '9');
}

u8 ischar(char c) {
    return ( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ); 
}

s32 tolower(s32 c) {
    if (ischar(c)) c |= 0x20;
    return c;
}
