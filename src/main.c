#include "common.h"
#include "gpio.h"
#include "uart.h"

void wait(u64 cycles);

int main(void) {
    sel_gpio_func(4, OUTPUT_FUNC);
    set_gpio_output(4);

    test_uart();

    return 0;
}
