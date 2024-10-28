#include "gpio.h"
#include "uart.h"
#include "utils.h"

void init_uart0() {
    sel_gpio_func(GPIO_UART_RX0, ALT0_FUNC);
    conf_gpio_pupd(GPIO_UART_RX0, NO_RES);
    sel_gpio_func(GPIO_UART_TX0, ALT0_FUNC);
    conf_gpio_pupd(GPIO_UART_TX0, NO_RES);

    /* Configure line control register (8 bit Parity) */
    *REG_UART_LCRH(UART0) &= UART_LCRH_MASK;
    *REG_UART_LCRH(UART0) |= 0b01110000;     //0b0111 0000 

    /* Configure baudrate */
    *REG_UART_IBRD(UART0) = 26;
    *REG_UART_FBRD(UART0) = 3;

    /* Mask all interrupts */
    *REG_UART_IFLS(UART0) = UART_IFLS_MASK;
    *REG_UART_IMSC(UART0) = UART_IMSC_MASK;

    /* Configure line control (ENABLE UART) */
    *REG_UART_CR(UART0) &= UART_CR_MASK;
    *REG_UART_CR(UART0) |= 0b1100001100000001;  //0b1100 0011 0000 0001
}

void init_uart4() {
    sel_gpio_func(GPIO_UART_RX4, ALT4_FUNC);
    conf_gpio_pupd(GPIO_UART_RX4, NO_RES);
    sel_gpio_func(GPIO_UART_TX4, ALT4_FUNC);
    conf_gpio_pupd(GPIO_UART_TX4, NO_RES);

    /* Configure line control register (8 bit Parity) */
    *REG_UART_LCRH(UART4) &= UART_LCRH_MASK;
    *REG_UART_LCRH(UART4) |= 0x70;     //0b0111 0000

    /* Configure baudrate */
    *REG_UART_IBRD(UART4) = 26;
    *REG_UART_FBRD(UART4) = 3;

    /* Mask all interrupts */
    *REG_UART_IFLS(UART4) = UART_IFLS_MASK;
    *REG_UART_IMSC(UART4) = UART_IMSC_MASK;

    /* Configure line control (ENABLE UART) */
    *REG_UART_CR(UART4) &= UART_CR_MASK;
    *REG_UART_CR(UART4) |= 0b1100001100000001;  //0b1100 0001 0000 0001
}

void outbyte(char c) {
    /* Wait until transmission channel is empty */
    while ((*REG_UART_FR(UART4) & UART_FR_TXFF_BIT));
    /* Send the character */
    *REG_UART_DR(UART4) = (c & UART_DR_TX_MASK);
}

void uart_str(char *str) {
    for (; *str != 0; str++) outbyte(*str);
}

void uart_int(u64 num) {
    char nbuf[32];
    itos(num, nbuf);
    uart_str(nbuf);
}

void uart_hex(u64 num) {
    char nbuf[32];
    i16tos(num, nbuf);
    uart_str(nbuf);
}

void uart_nl() {
    outbyte('\n');
}
