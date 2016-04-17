#include <kernel/vga.h>
#include <kernel/asm.h>

//http://www.osdever.net/FreeVGA/vga/crtcreg.htm

//Returns the port address according to color mode
static uint16_t vga_port_crtc_get_address_port();
//Returns the port address according to color mode
static uint16_t vga_port_crtc_get_data_port();

//Sets all the specified flags to the boolean value
void vga_port_misc_set_flags(uint8_t flags, bool value) {
	uint8_t port_value = _inb(VGA_PORT_MISC_IN);
	if(value) {
		port_value |= flags;
	}
	else {
		port_value &= ~flags;
	}
	_outb(VGA_PORT_MISC_OUT, port_value);
}

uint8_t vga_port_misc_get_flags(uint8_t flags) {
	uint8_t port_value = _inb(VGA_PORT_MISC_IN);
	return port_value & flags;
}

uint16_t vga_port_crtc_get_address_port() {
	uint8_t color_mode = vga_port_misc_get_flags(VGA_MISC_IO_AS);
	if(color_mode) {
		return VGA_CRTC_COLOR_ADDRESS_PORT;
	}
	else {
		return VGA_CRTC_MONOCHROME_ADDRESS_PORT;
	}
}

uint16_t vga_port_crtc_get_data_port() {
	uint8_t color_mode = vga_port_misc_get_flags(VGA_MISC_IO_AS);
	if(color_mode) {
		return VGA_CRTC_COLOR_DATA_PORT;
	}
	else {
		return VGA_CRTC_MONOCHROME_DATA_PORT;
	}
}

uint8_t vga_port_crtc_get(uint8_t register_address) {
	uint16_t port_address = vga_port_crtc_get_address_port();
	uint16_t port_data = vga_port_crtc_get_data_port();
	
	_outb(port_address, register_address);
	uint8_t register_data = _inb(port_data);
	return register_data;
}

void vga_port_crtc_set(uint8_t register_address, uint8_t value) {
	uint16_t port_address = vga_port_crtc_get_address_port();
	uint16_t port_data = vga_port_crtc_get_data_port();
	
	_outb(port_address, register_address);
	_outb(port_data, value);
}