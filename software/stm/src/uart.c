#include "uart.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <stdbool.h>
#include <stdio.h>

struct pds_control control;
struct pds_feedback feedback;

// TEMPORARY:
//  TODO: switch to usb-cdc implementation
void uart_init(void) {
  rcc_periph_clock_enable(RCC_USART1);

  usart_set_baudrate(COMM_USART, 1000000);  // 1Mbaud
  usart_set_mode(COMM_USART, USART_MODE_TX_RX);

  usart_enable_tx_dma(COMM_USART);
  usart_enable_rx_dma(COMM_USART);

  usart_enable(COMM_USART);
}

// Send one copy of the feedback struct over UART
void uart_feedback_tx(void) {
  // DMA?
}
