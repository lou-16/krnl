#include "BGA.h"

#include "../pci/pci.h"

framebuffer_t framebuffer;

res_info_t res_info;

uint16_t bga_read_register(uint16_t value_to_read)
{
    // write the index value to index ioport
    outw(VBE_DISPI_IOPORT_INDEX, value_to_read);
    //now we must read the 16-bit value from data port
    return inw(VBE_DISPI_IOPORT_DATA);
}

bool bga_set_register(uint16_t value_to_set, uint16_t register_to_set)
{
    outw(VBE_DISPI_IOPORT_INDEX, register_to_set);
    outw(VBE_DISPI_IOPORT_DATA, value_to_set);

}

void bga_disable_extensions()
{
    outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_ENABLE);
    outw(VBE_DISPI_IOPORT_DATA, VBE_DISPI_DISABLED);
}

void bga_enable_extensions()
{
    outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_ENABLE);
    outw(VBE_DISPI_IOPORT_DATA, VBE_DISPI_ENABLED);
}

bool bga_check_availability(){

    // first we must send query for the id
    outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_ID);
    // to check for availability, we must read id from index port
    uint16_t id = inw(VBE_DISPI_IOPORT_DATA);
    if(id <= VBE_DISPI_ID5 && id >= VBE_DISPI_ID0)
    {
        return true;
    }
    else return false;
}

void bga_set_resolution(uint16_t width, uint16_t height)
{
    // first disable the VBE extensions
    bga_disable_extensions();

    // now write the new values. i want a 800x600 16-bit display
    outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_XRES);
    outw(VBE_DISPI_IOPORT_DATA, width);

    outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_YRES);
    outw(VBE_DISPI_IOPORT_DATA, height);

    outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_BPP);
    outw(VBE_DISPI_IOPORT_DATA, VBE_DISPI_BPP_16);

    // now we must check if our resolution is set

    if(bga_read_register(VBE_DISPI_INDEX_XRES) == width && bga_read_register(VBE_DISPI_INDEX_YRES) == height)
    {
        serial_write_string("[BGA] resolution set");   
        outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_ENABLE);
        outw(VBE_DISPI_IOPORT_DATA, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);
    
        res_info.bpp = 16;
        res_info.x = width;
        res_info.y = height;

    }
    else {
        serial_write_string("[BGA] resolution did not set");
        res_info.bpp = 0;
        res_info.x = 0;
        res_info.y = 0;
    }
    return;
}

uint16_t bga_set_lfb_mode(bool status){
    return status? VBE_DISPI_LFB_ENABLED : 0x0;
}

uint32_t bga_get_fb_size()
{
    uint16_t w = bga_read_register(VBE_DISPI_INDEX_XRES);
    uint16_t h = bga_read_register(VBE_DISPI_INDEX_YRES);
    uint32_t d = bga_read_register(VBE_DISPI_INDEX_BPP);

    return (uint32_t)w * h * (d / 8);
}

uint32_t bga_get_lfb_loc()
{
    uint32_t id = pci_config_read32(0, 2, 0, 0);
    uint16_t vendor = id & 0xFFFF;
    uint16_t device = (id >> 16);
    
    uint32_t framebuffer_addr;

    if(vendor == 0x1234 && device == 0x1111)
    {
        uint32_t bar0 = pci_config_read32(0, 2, 0, 0x10);
        framebuffer_addr = bar0 & 0xFFFFFFF0;
    }

    framebuffer.fb = framebuffer_addr;
    framebuffer.fb_size = bga_get_fb_size();

    return framebuffer_addr;
}

uint32_t bga_enable()
{
    if(!bga_check_availability())
    {
        return 0;
    }
    bga_set_resolution(800, 600);
    return bga_get_lfb_loc();
}

void bga_test_fill(uint32_t fb_addr, uint16_t width, uint16_t height)
{
    volatile uint16_t* fb = (volatile uint16_t*)fb_addr;

    serial_write_string("\n[BGA] Filling screen...\n");

    for (int y = 0; y < res_info.y; y++) {
        for (int x = 0; x < res_info.x; x++) {
            uint16_t color = RGB565(0, 0, 31);
            bga_putpixel(x, y, color);
        }
    }
    serial_write_string("[BGA] Framebuffer color test done\n");

    serial_write_string("[BGA] Done fill test.\n");
}

void bga_test()
{
    bga_test_fill(framebuffer.fb, res_info.x, res_info.y);
}

void bga_putpixel(uint16_t x, uint16_t y, uint16_t color)
{
    if(x >= res_info.x || y >= res_info.y)
    {
        return;
    }
    uint16_t* pixel_loc = (uint16_t*)framebuffer.fb + (y * res_info.x + x);
    *pixel_loc = color; 
    return;
}