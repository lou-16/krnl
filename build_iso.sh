#!/bin/bash

set -e

# Configurable paths
BUILD_DIR=build
ISO_DIR=iso
GRUB_DIR=$ISO_DIR/boot/grub
KERNEL_ELF_NAME=kernel.elf
ISO_OUTPUT=krnl.iso

# ------------------------------------------------------------------------------
echo "[+] Cleaning previous build..."
rm -rf "$BUILD_DIR" "$ISO_DIR" "$ISO_OUTPUT"

# ------------------------------------------------------------------------------
echo "[+] Creating build directory..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "[+] Running CMake..."
cmake .. > /dev/null

echo "[+] Building project..."
make -j$(nproc) > /dev/null

cd ..

# ------------------------------------------------------------------------------
echo "[+] Creating ISO directory structure..."
mkdir -p "$GRUB_DIR"

# Locate the ELF
KERNEL_ELF_PATH="$BUILD_DIR/$KERNEL_ELF_NAME"
if [ ! -f "$KERNEL_ELF_PATH" ]; then
    echo "❌ Error: $KERNEL_ELF_PATH not found. Make sure your target is named $KERNEL_ELF_NAME"
    exit 1
fi

echo "[+] Copying ELF: $KERNEL_ELF_PATH → $ISO_DIR/boot/$KERNEL_ELF_NAME"
cp "$KERNEL_ELF_PATH" "$ISO_DIR/boot/$KERNEL_ELF_NAME"

# ------------------------------------------------------------------------------
echo "[+] Writing GRUB configuration..."
cat > "$GRUB_DIR/grub.cfg" <<EOF
set timeout=0
set default=0

menuentry "My Kernel" {
    multiboot /boot/$KERNEL_ELF_NAME
    boot
}
EOF

# ------------------------------------------------------------------------------
echo "[+] Final ISO directory tree:"
tree "$ISO_DIR"

# ------------------------------------------------------------------------------
echo "[+] Building ISO with grub-mkrescue..."
grub-mkrescue -o "$ISO_OUTPUT" "$ISO_DIR" > /dev/null

echo "✅ ISO successfully created: $ISO_OUTPUT"
