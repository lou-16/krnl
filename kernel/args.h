#pragma once

#include <stdint.h>
#include <stdbool.h>

#define BOOT_MAX_ARGS 2

typedef enum display_mode {
    DM_VGA_TEXT = 0,
    DM_BOCHS
} DISPLAY_MODE ;

struct __boot_args__ {
    bool real_hardware;
    DISPLAY_MODE display_mode;
};

struct __boot_args__* parse_boot_args(uint32_t*);