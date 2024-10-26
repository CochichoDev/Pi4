#include "common.h"
#include "gpio.h"
#include "uart.h"
#include "printf.h"

void wait(u64 cycles);

int main(void) {
    init_uart0();
    puts("Hello World\n");
    printf("This is an integer: %d\n", 10);

    sel_gpio_func(4, OUTPUT_FUNC);
    set_gpio_output(4);
    return 0;
}
