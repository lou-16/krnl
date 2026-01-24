#!/bin/bash 

# deps: git, make
echo "Checking if Limine Exists..."
cd limine
if [[ $? != 0 ]]; then
    echo "Limine not found. peforming a git operation"
    cd ..
    git clone https://codeberg.org/Limine/Limine.git limine
    echo "Limine cloned. building ..."
    cd Limine
    make 
    echo "built limine"
    
fi
cd ..
# back to root
mkdir -p build
echo "Running CMake"
cd build
cmake ..

echo "Moving kernel.elf to iso"

cd ..
#back to root
mkdir -p iso
cp ./build/kernel.elf ./iso/

echo "moving Limine files to iso folder"
cp ./limine/limine-bios-cd.bin ./iso
cp ./limine/limine-bios.sys ./iso
cp ./limine/limine-uefi-cd.bin ./iso
cd iso
mkdir -p BOOT
cd ..
#back to root
cp ./limine/BOOTX64.EFI ./iso/BOOT
echo "moved Limine files to iso folder"

echo "creating limine.conf"
cat ./iso/BOOT/limine.conf << EOF
TIMEOUT=5

/krnl-x86_64
    protocol: limine
    kernel_path: boot():/kernel.elf" 
EOF

echo "checking if the tree path is fine PLEASE VERIFY"
tree ./iso

echo "building ISO"
xorriso -as mkisofs -R -J -b limine-bios-cd.bin \
    -no-emul-boot \
    -boot-load-size 4 \
    -boot-info-table \
    --efi-boot limine-uefi-cd.bin \
    --efi-boot-part --efi-boot-image \
    -o limine.iso ./iso
echo "Running limine bios-install"

./limine/limine bios-install limine.iso

echo "ISO prepared"