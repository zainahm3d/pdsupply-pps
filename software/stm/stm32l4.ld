/*
STM32L432KC has Flash memory beginning at 0x08000000
SRAM starts at 0x20000000

SRAM/ROM sizes vary - STM32L432KC is 256k flash, 64K sram
*/

MEMORY
{
	rom (rx) : ORIGIN = 0x08000000, LENGTH = 256K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

/* Include the common ld script. */
INCLUDE cortex-m-generic.ld