#include "uart.h"
#include "mbox.h"
#include "asm.h"

#define DEBUG

static __attribute__((aligned(16))) u32 buf[] = {
    32,     // Size of buffer
    0,      // Buffer request code
        0x00030002,     // Tag
        8,      // Buffer Size
        0,      // Tag request code
        0x000000004,      // Buffer1
        0,      // Buffer2
    0,      // End tag
};

void mbox_get_firmware_version() {
#ifdef DEBUG
    uart_str("Get firmware version function\n");
    uart_str("Sending a mbuffer to tag: "); uart_hex(buf[2]); uart_nl();
    uart_str("Address of MBOX_RW: "); uart_hex(PBASE+MBOX_OFF+MBOX_WR_OFF); uart_nl();
#endif

    while ( (*REG_MBOX_WR_ST & MBOX_ST_FULL_MASK) );

    uintptr_t mail = (uintptr_t) buf;

#ifdef DEBUG
    uart_str("Sending the following mail: "); uart_hex(mail); uart_nl();
    uart_str("Status Register: "); uart_hex(*REG_MBOX_WR_ST); uart_nl();
#endif

    mail &= ~(0xFU);
    mail |= 0x8;

    *REG_MBOX_WR = mail;

#ifdef DEBUG
    uart_str("Waiting for response: "); uart_hex(mail); uart_nl();
    uart_str("Status Register: "); uart_hex(*REG_MBOX_WR_ST); uart_nl();
#endif
    
    while ( (*REG_MBOX_RD_ST & MBOX_ST_EMPTY_MASK) );

#ifdef DEBUG
    uart_str("Message received\n");
    uart_str("Status Register: "); uart_hex(*REG_MBOX_RD_ST); uart_nl();
#endif

    mail = *REG_MBOX_RD;
    u8 channel = mail & 0xFU;
    mail &= ~(0xFU);

#ifdef DEBUG
    uart_str("Message read: "); uart_hex(mail); uart_nl();
    uart_str("Status Register: "); uart_hex(*REG_MBOX_RD_ST); uart_nl();
    uart_str("From channel: "); uart_hex(channel); uart_nl();
    uart_str("Status code: "); uart_hex(buf[1]); uart_nl();
#endif

    if (channel == 0x8) {
    #ifdef DEBUG
        uart_str("Response Code: "); uart_hex(buf[4]); uart_nl();
        uart_str("Response Size: "); uart_hex(buf[3]); uart_nl();
        uart_str("Buffer 1: "); uart_hex(buf[5]); uart_nl();
        uart_str("Buffer 2: "); uart_hex(buf[6]); uart_nl();
    #endif
    } else {
        uart_str("Response received by wrong channel\n");
    }
}
