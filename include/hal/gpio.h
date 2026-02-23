#pragma once
#include <stdint.h>

typedef enum {
    GPIO_INPUT,
    GPIO_OUTPUT
} gpio_mode_t;

typedef uint8_t gpio_pin_t;

#define GPIO_PORT_SHIFT 4
#define GPIO_MAKE_PIN(port, pin) (((port) << GPIO_PORT_SHIFT) | (pin))

#define PB0 GPIO_MAKE_PIN(1,0)
#define PB1 GPIO_MAKE_PIN(1,1)
#define PB2 GPIO_MAKE_PIN(1,2)
#define PB3 GPIO_MAKE_PIN(1,3)

void gpio_init(gpio_pin_t pin, gpio_mode_t mode);
void gpio_write(gpio_pin_t pin, uint8_t value);