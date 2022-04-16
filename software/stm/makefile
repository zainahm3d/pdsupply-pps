OBJS = $(patsubst %.c,%.o,$(wildcard src/*.c))

# We've got opencm3 in the folder with us
OPENCM3_DIR := ./libopencm3
OUTPUT_DIR := out
PROJ_NAME := pdsupply

# Our output name
BINARY = main

# Linker script for our MCU
LDSCRIPT = stm32l4.ld

# Using the stm32L4 series chip
LIBNAME		= opencm3_stm32L4
DEFS		+= -DSTM32L4

# Target-specific flags
FP_FLAGS	?= -mhard-float
ARCH_FLAGS	= -mthumb -mcpu=cortex-m4 $(FP_FLAGS)

## Boilerplate

# Compiler configuration
PREFIX		?= arm-none-eabi
CC		:= $(PREFIX)-gcc
LD		:= $(PREFIX)-gcc
AR		:= $(PREFIX)-ar
AS		:= $(PREFIX)-as
SIZE		:= $(PREFIX)-size
OBJCOPY		:= $(PREFIX)-objcopy
OBJDUMP		:= $(PREFIX)-objdump
GDB		:= $(PREFIX)-gdb
STFLASH		= $(shell which st-flash)
OPT		:= -Os
DEBUG		:= -ggdb3
CSTD		?= -std=c17

# C flags
TGT_CFLAGS	+= $(OPT) $(CSTD) $(DEBUG)
TGT_CFLAGS	+= $(ARCH_FLAGS)
TGT_CFLAGS	+= -Wextra -Wshadow -Wimplicit-function-declaration
TGT_CFLAGS	+= -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes
TGT_CFLAGS	+= -fno-common -ffunction-sections -fdata-sections

# C & C++ preprocessor common flags
TGT_CPPFLAGS	+= -MD
TGT_CPPFLAGS	+= -Wall -Wundef
TGT_CPPFLAGS	+= $(DEFS)

# Linker flags
TGT_LDFLAGS		+= --static -nostartfiles
TGT_LDFLAGS		+= -T$(LDSCRIPT)
TGT_LDFLAGS		+= $(ARCH_FLAGS) $(DEBUG)
TGT_LDFLAGS		+= -Wl,-Map=$(OUTPUT_DIR)/$(PROJ_NAME).map -Wl,--cref
TGT_LDFLAGS		+= -Wl,--gc-sections
ifeq ($(V),99)
TGT_LDFLAGS		+= -Wl,--print-gc-sections
endif

# Used libraries
DEFS		+= -I$(OPENCM3_DIR)/include
LDFLAGS		+= -L$(OPENCM3_DIR)/lib
LDLIBS		+= -l$(LIBNAME)
LDLIBS		+= -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

.SUFFIXES: .elf .bin .hex .srec .list .map .images
.SECONDEXPANSION:
.SECONDARY:

all: elf size
size: $(BINARY).size
elf: $(BINARY).elf
bin: $(BINARY).bin
hex: $(BINARY).hex
srec: $(BINARY).srec
list: $(BINARY).list

GENERATED_BINARIES=$(BINARY).elf $(BINARY).bin $(BINARY).hex $(BINARY).srec $(BINARY).list $(BINARY).map

%.bin: %.elf
	$(OBJCOPY) -Obinary $(*).elf $(*).bin

%.hex: %.elf
	$(OBJCOPY) -Oihex $(*).elf $(*).hex

%.srec: %.elf
	$(OBJCOPY) -Osrec $(*).elf $(*).srec

%.list: %.elf
	$(OBJDUMP) -S $(*).elf > $(*).list

%.elf %.map: $(OBJS) $(LDSCRIPT)
	$(LD) $(TGT_LDFLAGS) $(LDFLAGS) $(OUTPUT_DIR)/*.o $(LDLIBS) -o $(OUTPUT_DIR)/$(PROJ_NAME).elf

%.o: %.c
	$(shell mkdir $(OUTPUT_DIR))
	$(CC) $(TGT_CFLAGS) $(CFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $(OUTPUT_DIR)/$(notdir $(*).o) -c $(*).c

%.size: %.elf
	@echo "Output code size:"
	@$(SIZE) -A -d $(OUTPUT_DIR)/$(PROJ_NAME).elf | egrep 'text|data|bss' | awk ' \
    function human(x) { \
        if (x<1000) {return x} else {x/=1024} \
        s="kMGTEPZY"; \
        while (x>=1000 && length(s)>1) \
            {x/=1024; s=substr(s,2)} \
        return int(x+0.5) substr(s,1,1) \
    } \
	{printf("%10s %8s\n", $$1, human($$2))} \
'

clean:
	$(RM) $(GENERATED_BINARIES) generated.* $(OBJS) $(OBJS:%.o=%.d)
	$(shell rm -rf $(OUTPUT_DIR))

.PHONY: images clean elf bin hex srec list
-include $(OUTPUT_DIR$(OBJS:.o=.d)
