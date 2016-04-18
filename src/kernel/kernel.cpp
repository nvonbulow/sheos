#include <kernel/tty.h>
#include <kernel/multiboot_info.h>
#include <kernel/asm.h>
#include <stdio.h>
#include <multiboot.h>

#ifndef __IKERNEL__
#error "You are not building the kernel correctly."
#endif

extern void* _start;

void print_memory_map(multiboot_info_t* mbi) {
	multiboot_memory_map_t* mmap = (multiboot_memory_map_t*) mbi->mmap_addr;
	uint32_t mmap_length = mbi->mmap_length;
	
	printf("memory map located at 0x%x; %d entries\n", mmap, mmap_length);
	
	for(mmap = (multiboot_memory_map_t*) mbi->mmap_addr;
			(uint32_t) mmap < mbi->mmap_addr + mbi->mmap_length;
			mmap = (multiboot_memory_map_t*) ((uint32_t) mmap + mmap->size + sizeof(mmap->size))) {
		
		//uint32_t entry_size = mmap->size;
		uint64_t entry_addr = mmap->addr;
		uint64_t entry_len = mmap->len;
		uint32_t entry_type = mmap->type;
		
		char* entry_type_str;
		if(entry_type == MULTIBOOT_MEMORY_AVAILABLE) {
			entry_type_str = "available";
		}
		else if(entry_type == MULTIBOOT_MEMORY_RESERVED) {
			entry_type_str = "reserved";
		}
		else {
			entry_type_str = "unknown";
		}
		printf("Entry at 0x%x%x is length 0x%x%x and is %s.\n",
			(uint32_t) (entry_addr >> 32), (uint32_t) (entry_addr & 0xffffffff),
			(uint32_t) (entry_len >> 32), (uint32_t) (entry_len & 0xffffffff),
			entry_type_str);
	}
}

extern "C" void kernel_main(unsigned long magic, multiboot_info_t* mbi) {
	tty_init();
	//printf("kernel starts at 0x%x%x\n", (uint32_t) ((uint64_t)&_start >> 32), (uint32_t) ((uint64_t)&_start & 0xffffffff));
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		printf("Please load the kernel with a multiboot compliant bootloader!\n");
		return;
	}
	multiboot mboot(mbi);
	if(mboot.has_memory_map()) {
		print_memory_map(mbi);
	}
}