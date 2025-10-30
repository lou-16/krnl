#!/bin/bash

set -e

# ------------------------------------------------------------------------------
# 🎨 Colors
RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
CYAN="\033[1;36m"
RESET="\033[0m"
BOLD="\033[1m"

# ------------------------------------------------------------------------------
# Configurable paths
BUILD_DIR=build
ISO_DIR=iso
GRUB_DIR=$ISO_DIR/boot/grub
KERNEL_ELF_NAME=kernel.elf
ISO_OUTPUT=krnl.iso

# ------------------------------------------------------------------------------
echo -e "${CYAN}[${BOLD}+${RESET}${CYAN}] Cleaning previous build...${RESET}"
rm -rf "$BUILD_DIR" "$ISO_DIR" "$ISO_OUTPUT"

# ------------------------------------------------------------------------------
echo -e "${CYAN}[${BOLD}+${RESET}${CYAN}] Creating build directory...${RESET}"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo -e "${CYAN}[${BOLD}+${RESET}${CYAN}] Running CMake...${RESET}"
cmake .. > /dev/null

echo -e "${CYAN}[${BOLD}+${RESET}${CYAN}] Building project...${RESET}"
make -j$(nproc) > /dev/null

cd ..

# ------------------------------------------------------------------------------
echo -e "\n${CYAN}[${BOLD}+${RESET}${CYAN}] Creating ISO directory structure...${RESET}"
mkdir -p "$GRUB_DIR"

# Locate the ELF
KERNEL_ELF_PATH="$BUILD_DIR/$KERNEL_ELF_NAME"
if [ ! -f "$KERNEL_ELF_PATH" ]; then
    echo -e "${RED}❌ Error:${RESET} ${BOLD}$KERNEL_ELF_PATH${RESET} not found. Make sure your target is named ${YELLOW}$KERNEL_ELF_NAME${RESET}"
    exit 1
fi

echo -e "${GREEN}[✔]${RESET} Copying ELF: ${YELLOW}$KERNEL_ELF_PATH${RESET} → ${BLUE}$ISO_DIR/boot/$KERNEL_ELF_NAME${RESET}"
cp "$KERNEL_ELF_PATH" "$ISO_DIR/boot/$KERNEL_ELF_NAME"

# ------------------------------------------------------------------------------
echo -e "${CYAN}[${BOLD}+${RESET}${CYAN}] Writing GRUB configuration...${RESET}"
cat > "$GRUB_DIR/grub.cfg" <<EOF
set timeout=0
set default=0

menuentry "My Kernel" {
    multiboot /boot/$KERNEL_ELF_NAME
    boot
}
EOF

# ------------------------------------------------------------------------------
echo -e "\n${CYAN}[${BOLD}+${RESET}${CYAN}] Final ISO directory tree:${RESET}"
tree "$ISO_DIR"

# ------------------------------------------------------------------------------
echo -e "\n${CYAN}[${BOLD}+${RESET}${CYAN}] Building ISO with grub-mkrescue...${RESET}"
grub-mkrescue -o "$ISO_OUTPUT" "$ISO_DIR" > /dev/null

echo -e "\n${GREEN}✅ ISO successfully created:${RESET} ${BOLD}$ISO_OUTPUT${RESET}\n"
