include common.mk

LINKER = linker/linker.ld

SUBDIRS = libc

OBJECTS := 
LIBS := 

INCLUDE_DIRS = kernel/include libc/include
INCLUDE_FILES = $(shell find . -name "*.h" -type f -print0)
INCLUDE_DIR_FILES = $(foreach d, $(INCLUDE_DIRS), $d/*)

include boot/boot.mk
include kernel/kernel.mk

.PHONY: all $(SUBDIRS)

all: $(SUBDIRS) kernel.elf

kernel.elf: $(OBJECTS) $(LINKER)
	$(LD) -T $(LINKER) -o$@ $(OBJECTS) $(LD_FLAGS)
	
$(SUBDIRS): sysroot
	$(MAKE) -C $@

sysroot:
	mkdir -p $(BASE_DIR)/usr/include
	mkdir -p $(BASE_DIR)/usr/lib
	cp -R $(INCLUDE_DIR_FILES) $(BASE_DIR)/usr/include