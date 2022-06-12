#include "init.h"

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/usart.h>

#include "board.h"

static void clock_setup(void) {
  rcc_osc_on(RCC_HSI16);

  flash_prefetch_enable();
  flash_set_ws(4);
  flash_dcache_enable();
  flash_icache_enable();
  /* 16MHz / 4 = > 4 * 40 = 160MHz VCO => 80MHz main pll  */
  rcc_set_main_pll(RCC_PLLCFGR_PLLSRC_HSI16, 4, 40, 0, 0,
                   RCC_PLLCFGR_PLLR_DIV2);
  rcc_osc_on(RCC_PLL);
  /* either rcc_wait_for_osc_ready() or do other things */

  /* Enable clocks for peripherals we need */
  // rcc_periph_clock_enable(RCC_USART2);
  //     rcc_periph_clock_enable(RCC_TIM7);
  // rcc_periph_clock_enable(RCC_SYSCFG);

  rcc_set_sysclk_source(RCC_CFGR_SW_PLL); /* careful with the param here! */
  rcc_wait_for_sysclk_status(RCC_PLL);
  /* FIXME - eventually handled internally */
  rcc_ahb_frequency = 80e6;
  rcc_apb1_frequency = 80e6;
  rcc_apb2_frequency = 80e6;
}

static void systick_init(void) {
  // init 10ms systick here
}

static void gpio_init(void) {
  /* Enable clocks for the ports we need */
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB);
  rcc_periph_clock_enable(RCC_GPIOC);
  rcc_periph_clock_enable(RCC_GPIOD);
  rcc_periph_clock_enable(RCC_GPIOE);

  gpio_setup(GREEN_LED_PIN, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE);
  gpio_write(GREEN_LED_PIN, 0);
}

void init_micro(void) {
  clock_setup();
  systick_init();
  gpio_init();
}
