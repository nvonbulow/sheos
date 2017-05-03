#include <stdint.h>
#include <stdbool.h>
#include <kernel/asm.h>

#ifndef __KERNEL_VGA_H__
#define __KERNEL_VGA_H__

namespace kernel {
    namespace vga {
        static const uint32_t VGA_WIDTH = 80;
        static const uint32_t VGA_HEIGHT = 25;

        //A VGA Color

        enum class Color {
            BLACK = 0,
            BLUE = 1,
            GREEN = 2,
            CYAN = 3,
            RED = 4,
            MAGENTA = 5,
            BROWN = 6,
            LIGHT_GREY = 7,
            DARK_GREY = 8,
            LIGHT_BLUE = 9,
            LIGHT_GREEN = 10,
            LIGHT_CYAN = 11,
            LIGHT_RED = 12,
            LIGHT_MAGENTA = 13,
            LIGHT_BROWN = 15,
            WHITE = 15
        };

        struct ColorEntry {
            Color background;
            Color foreground;
        };

        static inline ColorEntry make_color_entry(Color foreground, Color background) {
            ColorEntry ce;
            ce.foreground = foreground;
            ce.background = background;
            return ce;
        }

        namespace Ports {
            namespace Misc {
                static const uint16_t IN = 0x3CC;
                static const uint16_t OUT = 0x3C2;

                enum class MiscFlags {
                    VSYNCP = (1 << 7),
                    HSYNCP = (1 << 6),
                    OE_PAGE = (1 << 5),
                    CLOCK = ((1 << 3) | (1 << 2)),
                    RAM_EN = (1 << 1),
                    IO_AS = (1 << 0)
                };

                //Sets all the specified flags to the boolean value
                void set_flags(MiscFlags flags, bool value);

                //Gets the specified flags
                uint8_t get_flags(MiscFlags flags);
            }

            namespace Crtc {
                static const uint16_t MONOCHROME_ADDRESS = 0x3B4;
                static const uint16_t MONOCHROME_DATA = 0x3B5;
                static const uint16_t COLOR_ADDRESS = 0x3D4;
                static const uint16_t COLOR_DATA = 0x3D5;

                enum class Register {
                    HTR = 0x00,
                    EHD = 0x01,
                    SHB = 0x02,
                    EHB = 0x03,
                    SHR = 0x04,
                    EHR = 0x05,
                    VTR = 0x06,
                    OVR = 0x07,
                    PRS = 0x08,
                    MSL = 0x09,
                    CSR = 0x0A,
                    CER = 0x0B,
                    SAH = 0x0C,
                    SAL = 0x0D,
                    CLH = 0x0E,
                    CLL = 0x0F,
                    VRS = 0x10,
                    VRE = 0x11,
                    VDE = 0x12,
                    OFR = 0x13,
                    ULR = 0x14,
                    SVB = 0x15,
                    EVB = 0x16,
                    MCR = 0x17,
                    LCR = 0x18,
                };

                uint8_t get_register(Register r);
                void set_register(Register r, uint8_t value);
            }
        }
    }
}

#endif //__KERNEL_VGA_H__