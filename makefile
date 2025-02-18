# Cross compiler prefix
CC := i686-elf-gcc
LD := i686-elf-ld
AS := i686-elf-as
OBJCOPY := i686-elf-objcopy

# Directories
KERNEL_DIR := kernel
OBJ_DIR := obj

# Source files
KERNEL_SRCS := $(wildcard $(KERNEL_DIR)/*.c)
ASM_SRCS := $(wildcard $(KERNEL_DIR)/*.s)
KERNEL_OBJS := $(patsubst $(KERNEL_DIR)/%.c,$(OBJ_DIR)/%.o,$(KERNEL_SRCS))
ASM_OBJS := $(patsubst $(KERNEL_DIR)/%.s,$(OBJ_DIR)/%.o,$(ASM_SRCS))
LOADER_SRC := loader.s
LOADER_OBJ := $(OBJ_DIR)/loader.o

# Linker script
LINKER_SCRIPT := linker.ld

# Output files
KERNEL_ELF := krnl.elf
KERNEL_BIN := krnl.bin
DEBUG_SYM := krnl.sym

# Flags
CFLAGS := -g -ffreestanding -O0 -Wall -Wextra -I./libc/include/
LDFLAGS := -T $(LINKER_SCRIPT) -nostdlib

# Default target
all: $(KERNEL_BIN)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile assembly source
$(LOADER_OBJ): $(LOADER_SRC) | $(OBJ_DIR)
	$(AS) -o $@ $<

$(OBJ_DIR)/%.o: $(KERNEL_DIR)/%.s | $(OBJ_DIR)
	$(AS) -o $@ $<

# Compile C source files
$(OBJ_DIR)/%.o: $(KERNEL_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into ELF binary
$(KERNEL_ELF): $(KERNEL_OBJS) $(ASM_OBJS) $(LOADER_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^ 
	$(OBJCOPY) --only-keep-debug $@ $(DEBUG_SYM)

# Convert ELF to raw binary
$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) -O binary $< $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(KERNEL_ELF) $(KERNEL_BIN) $(DEBUG_SYM)

# Phony targets
.PHONY: all clean
