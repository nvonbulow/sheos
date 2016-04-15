export ARCH = i686-elf
export QEMU_ARCH = i386
export QEMU_PREFIX = qemu-system-
export QEMU = $(QEMU_PREFIX)$(QEMU_ARCH)

export BASE_DIR := $(shell pwd)

all:
	make -C src

run: all
	$(QEMU) -kernel src/kernel.elf
	rm trace*

strip: all
	$(ARCH)-strip src/kernel.elf
	
clean:
	find src -name "*.o" -type f -exec rm {} \;
	find src -name "*.elf" -type f -exec rm {} \;
	find src -name "*.bin" -type f -exec rm {} \;
	find src -name "*.a" -type f -exec rm {} \;
	rm -rf usr/
	rm -rf trace*