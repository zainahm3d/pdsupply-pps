#pragma once

#include <libopencm3/stm32/usart.h>
#include <stdbool.h>
#include <stdio.h>

static const uint32_t HOST_TIMEOUT_MS = 500;
static const uint32_t COMM_USART = USART1;

enum pds_status {
  STAT_DISABLED,
  STAT_ACTIVE,
  STAT_CURRENT_LIMITED,
  STAT_OVERCURRENT,
  STAT_HEADLESS,  // host USB disconnected
  STAT_TIMEOUT,   // host did not send a control packet in time
  STAT_FAULT,
};

// Command parameters for power supply.
struct __attribute__((packed)) pds_control {
  uint16_t millivolts;
  uint16_t milliamps;
  bool output_enable;
};

// Measured feedback data to host.
struct __attribute__((packed)) pds_feedback {
  uint16_t millivolts;
  uint16_t milliamps;
  bool output_enable;
  uint16_t max_supply_mv;  // max voltage supported by connected brick
  uint16_t max_supply_ma;  // mac current supported by connected brick
  enum pds_status status;  // indicate operating mode
};

void uart_init(void);
void uart_feedback_tx(void);
