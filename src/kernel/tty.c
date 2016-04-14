#include <kernel/vga.h>
#include <kernel/tty.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#define VGA_TTY_BUFFER_ADDRESS 0xB8000

//The VGA text buffer is mapped to 0xB8000
uint16_t* tty_buffer = (uint16_t*) VGA_TTY_BUFFER_ADDRESS;
//The row that the buffer is currently at
size_t tty_row = 0;
//The column that the buffer is currently at
size_t tty_column = 0;
//The current color of the terminal
vga_color tty_color = VGA_COLOR(COLOR_LIGHT_GREY, COLOR_BLACK);

//Creates a data structure suitable to put into the VGA buffer
inline uint16_t make_vga_entry(char c, vga_color color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

void tty_init() {
	tty_color = VGA_COLOR(COLOR_LIGHT_GREY, COLOR_BLACK);
	tty_column = 0;
	tty_row = 0;
	tty_buffer = (uint16_t*) 0xB8000;
	for(size_t y = 0; y < VGA_HEIGHT; y++) {
		for(size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			tty_buffer[index] = make_vga_entry(' ', tty_color);
		}
	}
}

void tty_set_color(vga_color color) {
	tty_color = color;
}

void tty_backspace() {
	//Prevent integer underflow
	if(tty_column == 0) {
		tty_column = VGA_WIDTH;
		//If switching rows, do it
		if(tty_row > 0) {
			tty_row--;
		}
	}
	//Decrement the column number
	tty_column--;
	//Clear the last character
	tty_putcharat(' ', tty_color, tty_row, tty_column);
}

//Shifts the buffer up x lines
void tty_shift(int lines) {
	//We end up discarding 'lines; lines
	
	//No point in shifting if it won't have an effect
	if(lines == 0) {
		return;
	}
	
	size_t copy_src = 0;
	size_t copy_dst = 0;
	
	//The amount of data to copy is total lines minus lines to discard
	size_t copy_length = VGA_WIDTH * VGA_HEIGHT - abs(lines) * VGA_WIDTH;
	//size_t copy_end = copy_src + copy_length; //unused
	
	//The empty entry to fill the discarded buffer with
	uint16_t empty_vga_entry = make_vga_entry(' ', tty_color);
	
	if(lines > 0) {
		//If we're moving up, then copy from lines 'lines' to the beginning
		//(crop off x lines)
		copy_src = lines * VGA_WIDTH;
		copy_dst = 0;
		
		//This only works if moving data from a higher memory location down
		//Otherwise you may overwrite buffer data
		for(size_t i = 0; i < copy_length; i++) {
			tty_buffer[copy_dst + i] = tty_buffer[copy_src + i];
		}
		for(size_t i = copy_length; i < VGA_WIDTH * VGA_HEIGHT; i++) {
			tty_buffer[i] = empty_vga_entry;
		}
	}
	else {
		//We're moving the buffer down, so copy the source so that the end of
		//the source is at the end of the buffer
		copy_src = 0;
		//Remember lines is negative currently
		copy_dst = -lines * VGA_WIDTH;
		
		
		
		for(size_t i = copy_src + copy_length - 1; i > copy_src; i--) {
			tty_buffer[copy_dst + i] = tty_buffer[copy_src + i];
		}
		tty_buffer[copy_dst] = tty_buffer[copy_src];
		for(size_t i = copy_src; i < copy_src + copy_dst; i++) {
			tty_buffer[i] = empty_vga_entry;
		}
	}
	
	tty_row -= lines;
	if(tty_row < 0) {
		tty_row = 0;
	}
	else if(tty_row >= VGA_HEIGHT) {
		tty_row = VGA_HEIGHT - 1;
	}
}

void tty_newline() {
	tty_row++;
	tty_column = 0;
	if(tty_row == VGA_HEIGHT) {
		tty_shift(1);
		tty_row--;
	}
}

//Prints a single character
char tty_putchar(const char c) {
	//Test for special cases such as newline and backspace
	switch(c) {
		case '\n':
			//tty_puts("tty_newline not yet implemented!!!");
			tty_newline();
			return c;
		case '\b':
			tty_backspace();
			return c;
		default:
			//Otherwise just do your normal thing
			tty_putcharat(c, tty_color, tty_row, tty_column);
	}
	if(++tty_column == VGA_WIDTH) {
		tty_newline();
	}
	return c;
}

void tty_puts(const char* str) {
	size_t datalen = strlen(str);
	for(size_t i = 0; i < datalen; i++) {
		tty_putchar(str[i]);
	}
	tty_putchar('\n');
}

//Puts a single character 
void tty_putcharat(const char c, vga_color color, size_t row, size_t column) {
	const size_t index = row * VGA_WIDTH + column;
	tty_buffer[index] = make_vga_entry(c, color);
}
