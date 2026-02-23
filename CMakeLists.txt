cmake_minimum_required(VERSION 3.20)
project(avr_hal C)

set(AVR_MCU atmega328p CACHE STRING "Target AVR MCU")
set(F_CPU 16000000UL CACHE STRING "CPU frequency")

add_library(avr_hal STATIC)

target_include_directories(avr_hal
    PUBLIC include
)

target_compile_options(avr_hal
    PUBLIC
        -mmcu=${AVR_MCU}
        -DF_CPU=${F_CPU}
        -Os -Wall -Wextra
)

target_link_options(avr_hal
    PUBLIC
        -mmcu=${AVR_MCU}
)

if(AVR_MCU STREQUAL "atmega328p")
    target_sources(avr_hal PRIVATE src/atmega328p/gpio.c)
endif()

add_subdirectory(examples/blink)

# ---- HEX generation ----
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/blink.hex
    COMMAND avr-objcopy -O ihex -R .eeprom
            $<TARGET_FILE:blink.elf>
            ${CMAKE_BINARY_DIR}/blink.hex
    DEPENDS blink.elf
    COMMENT "Generating HEX file"
)

add_custom_target(hex ALL
    DEPENDS ${CMAKE_BINARY_DIR}/blink.hex
)

# ---- Flash target ----
add_custom_target(flash
    COMMAND avr-objcopy -O ihex -R .eeprom
            $<TARGET_FILE:blink.elf>
            $<TARGET_FILE_DIR:blink.elf>/blink.hex
    COMMAND avrdude -c arduino -p m328p 
            -P /dev/ttyUSB0 -b 115200 
            -U flash:w:blink.hex
    DEPENDS hex
    COMMENT "Flashing firmaware"
)
