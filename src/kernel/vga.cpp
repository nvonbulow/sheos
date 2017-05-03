#include <kernel/vga.h>
#include <kernel/asm.h>

//http://www.osdever.net/FreeVGA/vga/crtcreg.htm

using namespace kernel;
using namespace kernel::vga;
namespace kernel {
	namespace vga {
		uint8_t Ports::Misc::get_flags(MiscFlags flags) {
			uint8_t port_value = _inb(Misc::IN);
			return port_value & (uint8_t) flags;
		}

		void Ports::Misc::set_flags(MiscFlags flags, bool value) {
			uint8_t port_value = _inb(Ports::Misc::IN);
			if(value) {
				port_value |= (uint8_t) flags;
			}
			else {
				port_value &= ~((uint8_t)flags);
			}
			_outb(Ports::Misc::OUT, port_value);
		}

		static uint16_t crtc_address_port() {
			uint8_t color_mode = vga::Ports::Misc::get_flags(vga::Ports::Misc::MiscFlags::IO_AS);
			if(color_mode) {
				return vga::Ports::Crtc::COLOR_ADDRESS;
			}
			else {
				return vga::Ports::Crtc::MONOCHROME_ADDRESS;
			}
		}

		static uint16_t crtc_data_port() {
			uint8_t color_mode = vga::Ports::Misc::get_flags(vga::Ports::Misc::MiscFlags::IO_AS);
			if(color_mode) {
				return vga::Ports::Crtc::COLOR_DATA;
			}
			else {
				return vga::Ports::Crtc::MONOCHROME_DATA;
			}
		}

		uint8_t Ports::Crtc::get_register(Register r) {
			uint16_t address_port = crtc_address_port();
			uint16_t data_port = crtc_data_port();

			_outb(address_port, (uint8_t) r);
			uint8_t register_data = _inb(data_port);
			return register_data;
		}

		void Ports::Crtc::set_register(Register r, uint8_t value) {
			uint16_t address_port = crtc_address_port();
			uint16_t data_port = crtc_data_port();

			_outb(address_port, (uint8_t) r);
			_outb(data_port, value);
		}
	}
}
	