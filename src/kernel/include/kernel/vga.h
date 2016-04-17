#include <stdint.h>
#include <stdbool.h>
#include <kernel/asm.h>

#ifndef __KERNEL_VGA_H__
#define __KERNEL_VGA_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Hardware text mode color constants. */
enum vga_color_const {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

typedef uint8_t vga_color;

#define VGA_COLOR(fg, bg) (fg | bg << 4)

inline vga_color make_vga_color(enum vga_color_const fg, enum vga_color_const bg) {
	return VGA_COLOR(fg, bg);
}

//The VGA Miscellaneous Output Registers
#define VGA_PORT_MISC_OUT 0x3C2
#define VGA_PORT_MISC_IN  0x3CC

//Define the bit constants for the ports

/* Vertical Sync Polarity
Determines the polarity of the vertical sync pulse and can be used
(with HSP) to control the vertical size of the display by utilizing the
autosynchronization feature of VGA displays.
	0 selects a positive vertical retrace sync pulse.
*/
#define VGA_MISC_VSYNCP (1<<7)
/* Horizontal Sync Polarity
Determines the polarity of the horizontal sync pulse
	0 selects a positive horizontal retrace sync pulse
*/
#define VGA_MISC_HSYNCP (1<<6)
/* Odd/Even Page select
Selects the upper/lower 64K page of memory when the system is in an even/odd
mode (modes 0,1,2,3,7).
	0 selects the low page
	1 selects the high page
*/
#define VGA_MISC_OE_PAGE

#define VGA_MISC_CS1 (1<<3)
#define VGA_MISC_CS2 (1<<2)
/* Clock Select
This field controls the selection of the dot clocks used in driving the display
timing. The standard hardware has 2 clocks available to it, nominally 25 Mhz
and 28 Mhz.  It is possible that there may be other "external" clocks that can
be selected by programming this register with the undefined values.  The
possible valuse of this register are:
	00 -- select 25 Mhz clock (used for 320/640 pixel wide modes)
	01 -- select 28 Mhz clock (used for 360/720 pixel wide modes)
	10 -- undefined (possible external clock)
	11 -- undefined (possible external clock)
*/
#define VGA_MISC_CLOCK (VGA_MISC_CS1 | VGA_MISC_CS2)
/* Ram Enable
Controls access to the display buffer
	0 disables address decode for the display buffer from the system
	1 enables
*/
#define VGA_MISC_RAM_EN (1<<1)
/* Input/Output Address Select
This bit selects the CRT controller addresses.
	0 sets the CRT controller addresses to 0x03Bx and the address for the Input
		Status Register 1 to 0x03BA for compatibility withthe monochrome
		adapter.
	1 sets CRT the controller addresses to 0x03Dx and the Input Status Register
		1 address to 0x03DA for compatibility with the color/graphics adapter.
		The Write addresses to the Feature Control register are affected in the
		same manner.
*/
#define VGA_MISC_IO_AS (1<<0)

//Sets all the specified flags to the boolean value
void vga_port_misc_set_flags(uint8_t flags, bool value);

//Gets the specified flags
uint8_t vga_port_misc_get_flags(uint8_t flags);

#define VGA_CRTC_MONOCHROME_ADDRESS_PORT 0x3B4
#define VGA_CRTC_MONOCHROME_DATA_PORT    0x3B5
#define VGA_CRTC_COLOR_ADDRESS_PORT      0x3D4
#define VGA_CRTC_COLOR_DATA_PORT         0x3D5

//Gets a value stored in the VGA crt controller
uint8_t vga_port_crtc_get(uint8_t register_address);
//Sets a value to the VGA crt controller
void vga_port_crtc_set(uint8_t register_address, uint8_t value);

//The CRTC Registers
//See http://www.osdever.net/FreeVGA/vga/crtcreg.htm for more information

//Horizontal Total
#define VGA_CRTC_HTR 0x00

//End Horizontal Display
#define VGA_CRTC_EHD 0x01

//Start Horizontal Blanking
#define VGA_CRTC_SHB 0x02

//End Horizontal Blanking
#define VGA_CRTC_EHB 0x03

//Start Horizontal Retrace
#define VGA_CRTC_SHR 0x04

//End Horizontal Retrace
#define VGA_CRTC_EHR 0x05

//Vertical Total
#define VGA_CRTC_VTR 0x06

//Overflow
#define VGA_CRTC_OVR 0x07

//Preset Row Scan
#define VGA_CRTC_PRS 0x08

//Maximum Scan Line
#define VGA_CRTC_MSL 0x09

//Cursor Start
#define VGA_CRTC_CSR 0x0A

//Cursor End
#define VGA_CRTC_CER 0x0B

//Start Address High
#define VGA_CRTC_SAH 0x0C

//Start Address Low
#define VGA_CRTC_SAL 0x0D

//Cursor Location High
#define VGA_CRTC_CLH 0x0E

//Cursor Location Low
#define VGA_CRTC_CLL 0x0F

//Vertical Retrace Start
#define VGA_CRTC_VRS 0x10

//Vertical Retrace End
#define VGA_CRTC_VRE 0x11

//Vertical Display End
#define VGA_CRTC_VDE 0x12

//Offset Register
#define VGA_CRTC_OFR 0x13

//Underline Location
#define VGA_CRTC_ULR 0x14

//Start Vertical Blanking
#define VGA_CRTC_SVB 0x15

//End Vertical Blanking
#define VGA_CRTC_EVB 0x16

//Mode Control
#define VGA_CRTC_MCR 0x17

//Line Compare
#define VGA_CRTC_LCR 0x18

#ifdef __cplusplus
}
#endif

#endif //__SYS_VGA_H__