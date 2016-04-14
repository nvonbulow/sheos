#include <kernel/vga.h>
#include <stddef.h>

#ifndef __KERNEL_TTY_H__
#define __KERNEL_TTY_H__

//The number of columns
#define VGA_WIDTH 80
//The number of rows
#define VGA_HEIGHT 25

#ifdef __cplusplus
extern "C" {
#endif

//Prints a single character to the tty screen
char tty_putchar(const char c);

//Prints a whole string to the tty buffer
void tty_puts(const char* str);

//Change a single character in the buffer
void tty_putcharat(const char c, vga_color color, size_t row, size_t column);

//Set the color of the terminal from here on out
void tty_set_color(vga_color color);

void tty_init();

#define tty_clear tty_init

#ifdef __cplusplus
}
#endif

#endif //__KERNEL_TTY_H__