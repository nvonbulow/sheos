export PLATFORM = x86_64
export ARCH = $(PLATFORM)-elf
QEMU_ARCH = i386
QEMU_PREFIX = qemu-system-
QEMU = $(QEMU_PREFIX)$(QEMU_ARCH)
GDB = $(ARCH)-gdb

EXECUTABLE = src/kernel.elf

export BASE_DIR := $(shell pwd)

all:
	make -C src

run: debug
	#$(QEMU) -kernel $(EXECUTABLE)
	#rm trace*

debug: all
	trap '' SIGINT
	$(QEMU) -kernel src/kernel.elf -s -S
	#$(GDB) --symbols=$(EXECUTABLE) -ex="target remote localhost:1234" -q --tui
	rm trace*

strip: all
	$(ARCH)-strip $(EXECUTABLE)
	
clean:
	find src -name "*.o" -type f -exec rm {} \;
	find src -name "*.elf" -type f -exec rm {} \;
	find src -name "*.bin" -type f -exec rm {} \;
	find src -name "*.a" -type f -exec rm {} \;
	rm -rf usr/
	rm -rf trace*
	rm -rf src/sysroot
