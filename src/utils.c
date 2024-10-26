#include "common.h"

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
