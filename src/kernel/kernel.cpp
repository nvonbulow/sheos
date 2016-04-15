#include <kernel/tty.h>
#include <kernel/multiboot_info.h>
#include <stdio.h>
#include <multiboot.h>

#ifndef __IKERNEL__
#error "You are not building the kernel correctly."
#endif

extern "C" void kernel_main(unsigned long magic, multiboot_info_t* mbi) {
	tty_init();
	
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		printf("Please load the kernel with a multiboot compliant bootloader!\n", (unsigned) magic);
		return;
	}
	multiboot mboot(mbi);
	
}