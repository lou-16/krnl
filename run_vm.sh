#!/bin/bash

DEBUG=""
DEBUG_LOG_FLAGS=""
DEBUG_GDB_CONN_ENABLE=""

if [[ $1 == "--debug" ]]; then
    DEBUG_LOG_FLAGS="-d int,cpu_reset"
    DEBUG_GDB_CONN_ENABLE="-S -s"
fi
qemu-system-i386 \
    -cdrom krnl.iso \
    -serial stdio \
    $DEBUG_LOG_FLAGS -D qemu.log \
    $DEBUG_GDB_CONN_ENABLE \