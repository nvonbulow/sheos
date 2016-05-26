SUBDIRS_REQUIREMENTS = sysroot

all: subdirs kernel.elf
	
export COMMON_MK = $(shell pwd)/common.mk

LINKER = linker/$(PLATFORM).ld

OBJECTS := 

INCLUDE_DIRS = $(shell find . -type d -name include -print)
INCLUDE_DIR_FILES = $(foreach d, $(INCLUDE_DIRS), $d/*)

INCLUDE_FILES = $(shell find . -name "*.h" -type f -print)

include boot/boot.mk
include kernel/kernel.mk

.PHONY: sysroot

sysroot: $(INCLUDE_FILES)
	mkdir -p $(BASE_DIR)/usr/include
	mkdir -p $(BASE_DIR)/usr/lib
	cp -R $(INCLUDE_DIR_FILES) $(BASE_DIR)/usr/include
	tar -cf $@ $(INCLUDE_FILES)

include common.mk

kernel.elf: $(OBJECTS) $(LINKER)
	$(LD) -T $(LINKER) -o$@ $(CRTBEGIN_OBJ) $(OBJECTS) $(CRTEND_OBJ) $(LD_FLAGS)