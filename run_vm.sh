#!/bin/bash

qemu-system-i386 -cdrom krnl.iso -serial stdio  -d int,cpu_reset -D qemu.log
