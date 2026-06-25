#!/bin/bash

qemu-system-i386 -smp 1 -cdrom krnl.iso -serial stdio  -d int,cpu_reset -D qemu.log
