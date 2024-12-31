# Cross compiler prefix
CC = i686-elf-gcc
LD = i686-elf-ld
AS = i686-elf-as
OBJCOPY = i686-elf-OBJCOPY
# Directories
KERNEL_DIR = kernel
OBJ_DIR = obj


# Source files
KERNEL_SRCS = $(wildcard $(KERNEL_DIR)/*.c)
KERNEL_OBJS = $(patsubst $(KERNEL_DIR)/%.c,$(OBJ_DIR)/%.o,$(KERNEL_SRCS))
LOADER_SRC = loader.s
LOADER_OBJ = $(OBJ_DIR)/loader.o

# Linker script
LINKER_SCRIPT = linker.ld

# Output kernel binary
KERNEL_BIN = krnl.bin

# Flags
CFLAGS = -ffreestanding -O0 -Wall -Wextra  -I./libc/include/
LDFLAGS =  -T $(LINKER_SCRIPT) -nostdlib
ASFLAGS = 

# Default target
all: $(KERNEL_BIN)

# Rule to create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to assemble loader.s into an object file
$(LOADER_OBJ): $(LOADER_SRC) | $(OBJ_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Rule to compile C source files into object files
$(OBJ_DIR)/%.o: $(KERNEL_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
# Rule to link object files into an ELF binary for debugging
krnl.elf: $(KERNEL_OBJS) $(LOADER_OBJ)
	$(LD) $(LDFLAGS) -o krnl.elf $(LOADER_OBJ) $(KERNEL_OBJS)

# Rule to link object files into the final kernel binary
$(KERNEL_BIN): krnl.elf
	$(OBJCOPY) -O binary krnl.elf $(KERNEL_BIN)

# Clean up the build artifacts
clean:
	rm -rf $(OBJ_DIR) $(KERNEL_BIN)

# Phony targets
.PHONY: all clean
