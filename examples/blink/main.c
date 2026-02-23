#include "hal/gpio.h"
#include <util/delay.h>

int main(void) {
    gpio_init(PB2, GPIO_OUTPUT);

    while (1) {
        gpio_write(PB2, 1);
        _delay_ms(500);
        gpio_write(PB2, 0);
        _delay_ms(500);
    }
}