#!/bin/bash
set -e

SCRIPT_DIR="$(cd -P "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"

echo "Checking if Limine exists..."

if [[ ! -d "$SCRIPT_DIR/limine" ]]; then
    echo "Limine not found. Cloning..."
    git clone https://codeberg.org/Limine/Limine.git "$SCRIPT_DIR/limine" \
        --branch=v10.x-binary --depth=1

    echo "Building Limine..."
    make -C "$SCRIPT_DIR/limine"
fi

echo "Running CMake..."
rm -rf "$SCRIPT_DIR/build"
mkdir -p "$SCRIPT_DIR/build"
cd "$SCRIPT_DIR/build"
cmake .. -DCMAKE_C_COMPILER=x86_64-elf-gcc
make

echo "Preparing ISO tree..."
mkdir -p "$SCRIPT_DIR/iso/BOOT"
cp "$SCRIPT_DIR/build/kernel.elf" "$SCRIPT_DIR/iso/"

cp "$SCRIPT_DIR/limine/limine-bios-cd.bin" "$SCRIPT_DIR/iso/"
cp "$SCRIPT_DIR/limine/limine-bios.sys" "$SCRIPT_DIR/iso/"
cp "$SCRIPT_DIR/limine/limine-uefi-cd.bin" "$SCRIPT_DIR/iso/"
cp "$SCRIPT_DIR/limine/BOOTX64.EFI" "$SCRIPT_DIR/iso/BOOT/"

echo "Creating limine.conf..."
cat << EOF > "$SCRIPT_DIR/iso/limine.conf"
TIMEOUT=5

/krnl-x86_64
    protocol: limine
    kernel_path: boot():/kernel.elf
EOF

echo "Building ISO..."
xorriso -as mkisofs \
    -R -J \
    -b limine-bios-cd.bin \
    -no-emul-boot \
    -boot-load-size 4 \
    -boot-info-table \
    --efi-boot limine-uefi-cd.bin \
    --efi-boot-part --efi-boot-image \
    -o "$SCRIPT_DIR/krnl-x86_64.iso" \
    "$SCRIPT_DIR/iso"

echo "Running limine bios-install..."
"$SCRIPT_DIR/limine/limine" bios-install "$SCRIPT_DIR/limine.iso"

echo "ISO prepared."
