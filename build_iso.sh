#!/bin/bash

set -e

# ------------------------------------------------------------------------------
# Colors
RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
CYAN="\033[1;36m"
RESET="\033[0m"
BOLD="\033[1m"

# ------------------------------------------------------------------------------
# Toolchain
CC="i686-elf-gcc"
CXX="i686-elf-g++"
AR="i686-elf-ar"
NM="i686-elf-nm"
STRIP="i686-elf-strip"
OBJCOPY="i686-elf-objcopy"

# ------------------------------------------------------------------------------
# Paths
BUILD_DIR=build
ISO_DIR=iso
GRUB_DIR=$ISO_DIR/boot/grub
KERNEL_ELF_NAME=kernel.elf
ISO_OUTPUT=krnl.iso

JOBS=$(getconf _NPROCESSORS_ONLN)

# ------------------------------------------------------------------------------
# Toolchain file
TOOLCHAIN_FILE="$(pwd)/cmake/cross-i386-elf.cmake"
mkdir -p "$(pwd)/cmake"

cat > "$TOOLCHAIN_FILE" <<EOF
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR i386)

set(CMAKE_C_COMPILER   $CC)
set(CMAKE_CXX_COMPILER $CXX)
set(CMAKE_AR           $AR)
set(CMAKE_NM           $NM)
set(CMAKE_STRIP        $STRIP)
set(CMAKE_OBJCOPY      $OBJCOPY)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
EOF

# ------------------------------------------------------------------------------
echo -e "${CYAN}[${BOLD}+${RESET}${CYAN}] Cleaning previous build...${RESET}"
rm -rf "$BUILD_DIR" "$ISO_DIR" "$ISO_OUTPUT"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo -e "${CYAN}[${BOLD}+${RESET}${CYAN}] Running CMake...${RESET}"
cmake .. --toolchain "$TOOLCHAIN_FILE"

echo -e "${CYAN}[${BOLD}+${RESET}${CYAN}] Building...${RESET}"
make -j"$JOBS" > /dev/null

cd ..

# ------------------------------------------------------------------------------
echo -e "\n${CYAN}[${BOLD}+${RESET}${CYAN}] Creating ISO structure...${RESET}"
mkdir -p "$GRUB_DIR"

KERNEL_ELF_PATH="$BUILD_DIR/$KERNEL_ELF_NAME"
if [ ! -f "$KERNEL_ELF_PATH" ]; then
    echo -e "${RED}❌ Error:${RESET} ${BOLD}$KERNEL_ELF_PATH${RESET} not found."
    exit 1
fi

echo -e "${GREEN}[✔]${RESET} ${YELLOW}$KERNEL_ELF_PATH${RESET} → ${BLUE}$ISO_DIR/boot/$KERNEL_ELF_NAME${RESET}"
cp "$KERNEL_ELF_PATH" "$ISO_DIR/boot/$KERNEL_ELF_NAME"

# ------------------------------------------------------------------------------
echo -e "${CYAN}[${BOLD}+${RESET}${CYAN}] Writing GRUB config...${RESET}"
cat > "$GRUB_DIR/grub.cfg" <<EOF
set timeout=-1
set default=0

menuentry "krnl" {
    multiboot /boot/$KERNEL_ELF_NAME
    boot
}
EOF

# ------------------------------------------------------------------------------
echo -e "\n${CYAN}[${BOLD}+${RESET}${CYAN}] ISO tree:${RESET}"
tree "$ISO_DIR"

echo -e "\n${CYAN}[${BOLD}+${RESET}${CYAN}] Building GRUB bootimage...${RESET}"
mkdir -p "$GRUB_DIR/i386-pc"


echo -e "\n${CYAN}[${BOLD}+${RESET}${CYAN}] Building ISO...${RESET}"
i686-elf-grub-mkrescue \
    -o krnl.iso \
    "$ISO_DIR"

echo -e "\n${GREEN}✅ Done:${RESET} ${BOLD}$ISO_OUTPUT${RESET}\n"