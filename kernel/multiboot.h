

#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

#define MULTIBOOT_MAGIC              0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC   0x2BADB002

// Multiboot flags
#define MULTIBOOT_FLAG_MEM           (1 << 0)
#define MULTIBOOT_FLAG_BOOT_DEVICE   (1 << 1)
#define MULTIBOOT_FLAG_CMDLINE       (1 << 2)
#define MULTIBOOT_FLAG_MODS          (1 << 3)
#define MULTIBOOT_FLAG_AOUT_SYMS     (1 << 4)
#define MULTIBOOT_FLAG_ELF_SECS      (1 << 5)
#define MULTIBOOT_FLAG_MMAP          (1 << 6)
#define MULTIBOOT_FLAG_DRIVES        (1 << 7)
#define MULTIBOOT_FLAG_CONFIG_TABLE  (1 << 8)
#define MULTIBOOT_FLAG_BOOT_LOADER   (1 << 9)
#define MULTIBOOT_FLAG_APM_TABLE     (1 << 10)
#define MULTIBOOT_FLAG_VBE           (1 << 11)
#define MULTIBOOT_FLAG_FRAMEBUFFER   (1 << 12)

typedef struct {
    uint32_t mod_start;
    uint32_t mod_end;
    uint32_t string;
    uint32_t reserved;
} __attribute__((packed)) multiboot_module_t;

typedef struct {
    uint32_t size;
    uint64_t addr;
    uint64_t len;
    uint32_t type;
} __attribute__((packed)) multiboot_memory_map_t;

typedef struct {
    uint32_t flags;

    uint32_t mem_lower;
    uint32_t mem_upper;

    uint32_t boot_device;
    uint32_t cmdline;

    uint32_t mods_count;
    uint32_t mods_addr;

    union {
        struct {
            uint32_t tabsize;
            uint32_t strsize;
            uint32_t addr;
            uint32_t reserved;
        } aout_sym;

        struct {
            uint32_t num;
            uint32_t size;
            uint32_t addr;
            uint32_t shndx;
        } elf_sec;
    } u;

    uint32_t mmap_length;
    uint32_t mmap_addr;

    uint32_t drives_length;
    uint32_t drives_addr;

    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t apm_table;

    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;

    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t  framebuffer_bpp;
    uint8_t  framebuffer_type;

    union {
        struct {
            uint32_t palette_addr;
            uint16_t palette_num_colors;
        };
        struct {
            uint8_t red_field_position;
            uint8_t red_mask_size;
            uint8_t green_field_position;
            uint8_t green_mask_size;
            uint8_t blue_field_position;
            uint8_t blue_mask_size;
        };
    };
} __attribute__((packed)) multiboot_info_t;

#endif
