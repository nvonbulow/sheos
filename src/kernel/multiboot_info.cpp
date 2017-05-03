#include <kernel/multiboot_info.h>
#include <multiboot.h>

namespace kernel {

	multiboot::multiboot(multiboot_info_t* info_header) {
		multiboot_header = info_header;
	}

	//The next several methods check the bits of flags

	bool multiboot::has_memory_info() {
		return multiboot_header->flags & MULTIBOOT_INFO_MEMORY;
	}

	bool multiboot::has_boot_device_info() {
		return multiboot_header->flags & MULTIBOOT_INFO_BOOTDEV;
	}

	bool multiboot::has_command_line() {
		return multiboot_header->flags & MULTIBOOT_INFO_CMDLINE;
	}

	bool multiboot::has_modules() {
		return multiboot_header->flags & MULTIBOOT_INFO_MODS;
	}

	bool multiboot::has_aout_symbols() {
		return multiboot_header->flags & MULTIBOOT_INFO_AOUT_SYMS;
	}

	bool multiboot::has_elf_header() {
		return multiboot_header->flags & MULTIBOOT_INFO_ELF_SHDR;
	}

	bool multiboot::has_memory_map() {
		return multiboot_header->flags & MULTIBOOT_INFO_MEM_MAP;
	}

	bool multiboot::has_drive_info() {
		return multiboot_header->flags & MULTIBOOT_INFO_DRIVE_INFO;
	}

	bool multiboot::has_config_table() {
		return multiboot_header->flags & MULTIBOOT_INFO_CONFIG_TABLE;
	}

	bool multiboot::has_bootloader_name() {
		return multiboot_header->flags & MULTIBOOT_INFO_BOOT_LOADER_NAME;
	}

	bool multiboot::has_apm_table() {
		return multiboot_header->flags & MULTIBOOT_INFO_APM_TABLE;
	}

	bool multiboot::has_video_info() {
		return multiboot_header->flags & MULTIBOOT_INFO_VIDEO_INFO;
	}

	uint32_t multiboot::get_memory_lower() {
		return multiboot_header->mem_lower;
	}

	uint32_t multiboot::get_memory_upper() {
		return multiboot_header->mem_upper;
	}

	uint32_t multiboot::get_boot_device() {
		return multiboot_header->boot_device;
	}

	char* multiboot::get_command_line() {
		return has_command_line() ? (char*) multiboot_header->cmdline : nullptr;
	}

}