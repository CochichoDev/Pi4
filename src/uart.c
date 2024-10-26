#include "gpio.h"
#include "uart.h"

void init_uart0() {
    sel_gpio_func(GPIO_UART_RX0, ALT0_FUNC);
    conf_gpio_pupd(GPIO_UART_RX0, NO_RES);
    sel_gpio_func(GPIO_UART_TX0, ALT0_FUNC);
    conf_gpio_pupd(GPIO_UART_TX0, NO_RES);

    /* Configure line control register (8 bit Parity) */
    *REG_UART_LCRH(UART0) &= UART_LCRH_MASK;
    *REG_UART_LCRH(UART0) |= 0b01100000;     //0b0110 0000 

    /* Configure baudrate */
    *REG_UART_IBRD(UART0) = 10;
    *REG_UART_FBRD(UART0) = 0;

    /* Configure line control (ENABLE UART) */
    *REG_UART_CR(UART0) &= UART_CR_MASK;
    *REG_UART_CR(UART0) |= 0b0000000100000001;  //0b0000 0001 0000 0001
}

void outbyte(char c) {
    /* Wait until transmission channel is empty */
    while ((*REG_UART_FR(UART0) & UART_CR_TXFF_BIT));
    /* Send the character */
    *REG_UART_DR(UART0) = (c & UART_DR_TX_MASK);
}
