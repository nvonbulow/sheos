#include <stdint.h>

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
	return fg | bg << 4;
}

#ifdef __cplusplus
}
#endif

#endif //__SYS_VGA_H__