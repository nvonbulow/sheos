#include <kernel/vga.h>
#include <stddef.h>
#include <stdint.h>

#ifndef __KERNEL_TTY_H__
#define __KERNEL_TTY_H__

namespace kernel {
    namespace tty {

        //Prints a single character to the VGA buffer
        char putchar(const char c);

        //Prints a null terminated string to the VGA buffer
        void puts(const char* str);

        //Changes a single character in the VGA buffer
        void putcharat(const char c, vga::ColorEntry color, size_t row, size_t column);

        //The characters printed from here on out will be this color
        void set_color(vga::Color foreground, vga::Color background);

        //Initializes the tty screen
        void init();

        //Clearing and initializing the buffer are exactly the same thing

        static inline void clear() {
            init();
        }

        //Changes where the buffer pointer points to
        void set_cursor(size_t row, size_t column);

    }
}

#endif //__KERNEL_TTY_H__