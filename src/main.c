#include "common.h"
#include "gpio.h"
#include "mbox.h"
#include "uart.h"
#include "asm.h"

int main(void) {
    sel_gpio_func(4, OUTPUT_FUNC);
    set_gpio_output(4);

    init_uart4();
    mbox_get_firmware_version();

    return 0;
}
