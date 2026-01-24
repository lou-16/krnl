#!/bin/bash

DEBUG_LOG_FLAGS=""
DEBUG_GDB_CONN_ENABLE=""
BOOT="-kernel build/kernel.elf"

if [[ "$1" == "--debug" || "$2" == "--debug" ]]; then
    DEBUG_LOG_FLAGS="-d int,cpu_reset"
    DEBUG_GDB_CONN_ENABLE="-S -s"
fi

if [[ "$1" == "--enable-grub" || "$2" == "--enable-grub" ]]; then
    BOOT="-cdrom krnl.iso"
fi

qemu-system-i386 \
    $BOOT \
    -serial stdio \
    $DEBUG_LOG_FLAGS -D qemu.log \
    $DEBUG_GDB_CONN_ENABLE
