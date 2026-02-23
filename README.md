# AVR HAL
Більшість проектів AVR будується на Arduino або пряме маніпулювання регістрами.

Цей проект забезпечує:
- Чисту архітектуру HAL
- Портативні драйвери
- Відсутність залежності від Arduino
- Повний контроль над ресурсами мікроконтролера
- Використання CMake як системи збірки

## Архітектура

```
avr-hal/
│
├── include/
│   └── hal/
│       └── gpio.h
│
├── src/
│   └── atmega328p/
│       └── gpio.c
└── examples/
```

## Підтримка
- atmega328p
- atmega8a (заплановано)
- attiny13a (Заплановано)

## Фічі
- CMake build system
- GPIO HAL

## Приклад
```c
#include "hal/gpio.h"
#include "util/delay.h"

int main() {
    gpio_init(PB2, GPIO_OUTPUT);

    while(1) {
        gpio_write(PB2, 1);
        _delay_ms(100);
        gpio_write(PB2, 0);
        _delay_ms(100);
    }
}
```
## Збірка
```
mkdir build
cd build

cmake ..

make
```

## Flash
```
make flash
```

## Заплановано

- SPI
- UART
- I2C
- Timers

## License

MIT
