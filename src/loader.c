#include "common.h"
#include "loader.h"
#include "uart.h"
#include "utils.h"
#include "gpio.h"
#include <stdint.h>

static u8 state = RUN;

static char *get_next_space(char *str) {
    while (*str != ' ' && *str != '\n') ++str;
    return str;
}

static char *get_next_char(char *str) {
    while ((!ischar(*str)) && *str != '\n') ++str;
    return str;
}

static char *get_next_digit(char *str) {
    while ((!isdigit(*str)) && *str != '\n') ++str;
    return str;
}

void loader_load_section(u8 *ptr, u64 size) {
    while (size-- > 0) {
        *ptr++ = inbyte();
    }
}

void loader_scan_action() {
    uart_str("LOADER STARTED\n\r");
    char input[64];
    char *ptr1, *ptr2;
    while (state) {
        uart_str("> ");
        ptr1 = input; ptr2 = input;
        get_uart_input(input, 64);
        sel_gpio_func(4, OUTPUT_FUNC);
        set_gpio_output(4);
        ptr1 = get_next_char(ptr1);
    
        if (!strncmp(ptr1, "LOAD", 4)) {
            ptr2 = get_next_digit(ptr1);
            u64 arg1 = parseUNum(ptr2, 59);;

            ptr2 = get_next_digit(get_next_space(ptr2));
            u64 arg2 = parseUNum(ptr2, 20);
    
            uart_str("LOAD section at address: ");
            uart_hex(arg1); uart_nl();
            uart_str("With size of: ");
            uart_hex(arg2); uart_nl();

            loader_load_section((u8 *)arg1, arg2);
        } else if (!strncmp(ptr1, "EXIT", 4)) {
            uart_str("EXITING...\n\r");
            state = STOP;
        }
    }
}
