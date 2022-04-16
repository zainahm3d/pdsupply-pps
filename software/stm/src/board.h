#pragma once

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/memorymap.h>
#include <stdio.h>

// Allows use of all in one port/pin definitions for gpio configuration.
inline void gpio_setup(uint32_t port, uint32_t pin, uint32_t mode,
                       uint32_t pull_up_down) {
  gpio_mode_setup(port, mode, pull_up_down, pin);
}

// Write high or low to a single GPIO pin
inline void gpio_write(uint32_t port, uint32_t pin, uint32_t state) {
  if (state) {
    gpio_set(port, pin);
  } else {
    gpio_clear(port, pin);
  }
}

#define GREEN_LED_PIN GPIOB, GPIO3
