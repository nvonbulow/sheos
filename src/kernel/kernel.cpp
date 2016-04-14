#include <kernel/vga.h>
#include <kernel/tty.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __IKERNEL__
#error "You are not building the kernel correctly."
#endif

extern "C" void tty_shift(int lines);

extern "C" void kernel_main() {
	tty_init();
	puts("Hello, world");
	puts("Hello, world");
	tty_shift(-24);
	tty_shift(1);
	tty_shift(23);
}