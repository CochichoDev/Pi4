#include "common.h"
#include "gpio.h"
#include "mbox.h"
#include "uart.h"
#include "asm.h"

int main(void) {
    mbox_set_uart_freq((BAUDRATE << 4)*10, 1);
    init_uart(BAUDRATE);
    sel_gpio_func(4, OUTPUT_FUNC);
    set_gpio_output(4);

    while (1)
        outbyte(inbyte());

    return 0;
}
