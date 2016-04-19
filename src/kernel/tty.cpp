#include <kernel/tty.h>
#include <kernel/vga.h>
#include <string.h>
#include <math.h>

using namespace kernel;
//using namespace kernel::tty;

static uint16_t* char_buffer = (uint16_t*) 0xB8000;

static size_t cursor_row = 0;
static size_t cursor_column = 0;

static vga::ColorEntry color =
		vga::make_color_entry(vga::Color::LIGHT_GREY, vga::Color::BLACK);

namespace kernel {
	namespace tty {
		
		static inline uint16_t make_vga_entry(char c, vga::ColorEntry color);
		static void newline();
		static void shift(int lines);
		static void backspace();
		
		void set_cursor(size_t row, size_t column) {
			using namespace vga::Ports;
			cursor_row = row;
			cursor_column = column;

			uint16_t cursor_location = (row * vga::VGA_WIDTH) + column;

			//Set the vga crtc registers CLL and CLH
			Crtc::set_register(Crtc::Register::CLL, (uint8_t) (cursor_location & 0xFF));
			Crtc::set_register(Crtc::Register::CLH, ((cursor_location >> 8) & 0xFF));
		}

		static inline uint16_t make_vga_entry(char c, vga::ColorEntry color) {
			uint16_t c16 = c;
			uint16_t color16 =
					((uint8_t) color.foreground | (uint8_t) color.background << 4);
			return c16 | color16 << 8;
		}

		static void shift(int lines) {
			//We end up discarding 'lines; lines

			//No point in shifting if it won't have an effect
			if(lines == 0) {
				return;
			}

			size_t copy_src = 0;
			size_t copy_dst = 0;

			//The amount of data to copy is total lines minus lines to discard
			size_t copy_length = vga::VGA_WIDTH * vga::VGA_HEIGHT -
					abs(lines) * vga::VGA_WIDTH;
			//size_t copy_end = copy_src + copy_length; //unused

			//The empty entry to fill the discarded buffer with
			uint16_t empty_vga_entry = make_vga_entry(' ', color);

			if(lines > 0) {
				//If we're moving up, then copy from lines 'lines' to the beginning
				//(crop off x lines)
				copy_src = lines * vga::VGA_WIDTH;
				copy_dst = 0;

				//This only works if moving data from a higher memory location down
				//Otherwise you may overwrite buffer data
				for(size_t i = 0;i < copy_length;i++) {
					char_buffer[copy_dst + i] = char_buffer[copy_src + i];
				}
				for(size_t i = copy_length;i < vga::VGA_WIDTH * vga::VGA_HEIGHT;i++) {
					char_buffer[i] = empty_vga_entry;
				}
			}
			else {
				//We're moving the buffer down, so copy the source so that the end of
				//the source is at the end of the buffer
				copy_src = 0;
				//Remember lines is negative currently
				copy_dst = -lines * vga::VGA_WIDTH;

				for(size_t i = copy_src + copy_length - 1;i > copy_src;i--) {
					char_buffer[copy_dst + i] = char_buffer[copy_src + i];
				}
				char_buffer[copy_dst] = char_buffer[copy_src];
				for(size_t i = copy_src;i < copy_src + copy_dst;i++) {
					char_buffer[i] = empty_vga_entry;
				}
			}

			if(((int) cursor_row) - lines < 0) {
				cursor_row = 0;
			}
			else if(((int32_t) cursor_row) - lines >= (signed) vga::VGA_HEIGHT) {
				cursor_row = vga::VGA_HEIGHT - 1;
			}
			else {
				cursor_row -= lines;
			}

			tty::set_cursor(cursor_row, cursor_column);
		}

		static void newline() {
			cursor_row++;
			cursor_column = 0;
			if(cursor_row >= vga::VGA_HEIGHT) {
				shift(1);
				cursor_row = vga::VGA_HEIGHT - 1;
			}
			tty::set_cursor(cursor_row, cursor_column);
		}

		static void backspace() {
			//Prevent integer underflow
			if(cursor_column == 0) {
				cursor_column = vga::VGA_WIDTH;
				//If switching rows, do it
				if(cursor_row > 0) {
					cursor_row--;
				}
			}
			//Decrement the column number
			cursor_column--;
			//Clear the last character
			tty::putcharat(' ', color, cursor_row, cursor_column);
			tty::set_cursor(cursor_row, cursor_column);
		}

		char putchar(const char c) {
			//Test for special cases such as newline and backspace
			switch(c) {
				case '\n':
					//tty_puts("tty_newline not yet implemented!!!");
					newline();
					return c;
				case '\b':
					backspace();
					return c;
				default:
					//Otherwise just do your normal thing
					tty::putcharat(c, color, cursor_row, cursor_column);
			}
			if(++cursor_column == vga::VGA_WIDTH) {
				newline();
			}
			tty::set_cursor(cursor_row, cursor_column);
			return c;
		}

		void puts(const char* str) {
			size_t datalen = strlen(str);
			for(size_t i = 0;i < datalen;i++) {
				tty::putchar(str[i]);
			}
			tty::putchar('\n');
		}

		void putcharat(const char c, vga::ColorEntry color, size_t row, size_t column) {
			const size_t index = (row * vga::VGA_WIDTH) + column;
			char_buffer[index] = make_vga_entry(c, color);
		}

		void set_color(vga::Color foreground, vga::Color background) {
			color = vga::make_color_entry(foreground, background);
		}

		void init() {
			color = vga::make_color_entry(vga::Color::LIGHT_GREY, vga::Color::BLACK);
			tty::set_cursor(0, 0);
			for(size_t y = 0;y < vga::VGA_HEIGHT;y++) {
				for(size_t x = 0;x < vga::VGA_WIDTH;x++) {
					const size_t index = y * vga::VGA_WIDTH + x;
					char_buffer[index] = tty::make_vga_entry(' ', color);
				}
			}
		}

	}
}
