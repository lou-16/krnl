#ifndef PCI_H
#define PCI_H

#include <stdint.h>
#include "../../kernel/io.h"

#define PCI_CONFIG_ADDR 0xCF8
#define PCI_CONFIG_DATA 0xCFC

uint32_t pci_config_read32(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset) {
    uint32_t address = 
        (1u << 31) |                // enable bit
        ((uint32_t)bus << 16) | 
        ((uint32_t)device << 11) |
        ((uint32_t)function << 8) |
        (offset & 0xFC);           // register offset (aligned)
    
    outl(PCI_CONFIG_ADDR, address);
    return inl(PCI_CONFIG_DATA);
}

#endif
