#include "hal/gpio.h"
#include <avr/io.h>

static volatile uint8_t* port_to_ddr(uint8_t port) {
    if (port == 1) return &DDRB;
    return 0;
}

static volatile uint8_t* port_to_port(uint8_t port) {
    if (port == 1) return &PORTB;
    return 0;
}

void gpio_init(gpio_pin_t pin, gpio_mode_t mode) {
    uint8_t port = pin >> GPIO_PORT_SHIFT;
    uint8_t bit  = pin & 0x0F;

    volatile uint8_t* ddr = port_to_ddr(port);
    if (!ddr) return;

    if (mode == GPIO_OUTPUT)
        *ddr |= (1 << bit);
    else
        *ddr &= ~(1 << bit);
}

void gpio_write(gpio_pin_t pin, uint8_t value) {
    uint8_t port = pin >> GPIO_PORT_SHIFT;
    uint8_t bit  = pin & 0x0F;

    volatile uint8_t* port_reg = port_to_port(port);
    if (!port_reg) return;

    if (value)
        *port_reg |= (1 << bit);
    else
        *port_reg &= ~(1 << bit);
}