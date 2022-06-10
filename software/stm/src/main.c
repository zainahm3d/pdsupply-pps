#include <stdio.h>

#include "init.h"
#include "uart.h"

int main(void) {
  init_micro();

  while (1) {
    testFunc();
  }
}