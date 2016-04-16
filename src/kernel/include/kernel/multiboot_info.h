#include <multiboot.h>
#include <stdint.h>

#ifndef __KERNEL_MULTIBOOT_INFO_H__
#define __KERNEL_MULTIBOOT_INFO_H__

#ifdef __cplusplus

class multiboot {
	private:
		multiboot_info_t* multiboot_header;
	public:
		multiboot(multiboot_info_t*);
		
		//The following check the flags
		bool has_memory_info();
		bool has_boot_device_info();
		bool has_command_line();
		bool has_modules();
		//aout and elf are mutally exclusive
		bool has_aout_symbols();
		bool has_elf_header();
		bool has_memory_map();
		bool has_drive_info();
		bool has_config_table();
		bool has_bootloader_name();
		bool has_apm_table();
		bool has_video_info();
		
		//Memory upper and lower bounds from the bios
		uint32_t get_memory_lower();
		uint32_t get_memory_upper();
		
		uint32_t get_boot_device();
		char* get_command_line();
};

#endif //__cplusplus

#endif //__KERNEL_MULTIBOOT_INFO_H__