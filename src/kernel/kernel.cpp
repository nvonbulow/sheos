#include <kernel/tty.h>
#include <stdio.h>
#include <multiboot.h>

#ifndef __IKERNEL__
#error "You are not building the kernel correctly."
#endif

extern "C" void kernel_main(unsigned long magic, multiboot_info_t* mbi) {
	tty_init();
	
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		printf("Invalid multiboot magic number: 0x%x\n", (unsigned) magic);
		return;
	}
	
	printf("Multiboot magic number is valid: 0x%x\n", (unsigned) magic);
	printf("The multiboot info structure is located at 0x%x\n", (unsigned) mbi);
}