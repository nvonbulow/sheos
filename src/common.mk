AS := $(ARCH)-as
AS_FLAGS := -I$(BASE_DIR)/multiboot

SYSROOT_INCLUDE_FILES = $(shell find "$(BASE_DIR)/usr/include" -name "*.h" -type f -print)

DEFINES := __IKERNEL__
DEFINES_PARAMS = $(foreach d, $(DEFINES), -D$d)

LIBS += gcc
LIBS_PARAMS = $(foreach d, $(LIBS), -l$d)

INCLUDES := "$(BASE_DIR)/multiboot"
INCLUDES_PARAMS = $(foreach d, $(INCLUDES), -I$d)

SYSROOT_FLAGS = --sysroot="$(BASE_DIR)" -isystem=/usr/include

WARNING_FLAGS = -Wno-write-strings -Wall -Wextra

SUBDIRS = $(shell find . -mindepth 2 -maxdepth 2 -name Makefile -printf "%h\n" | uniq)

CC := $(ARCH)-gcc
CC_FLAGS := $(SYSROOT_FLAGS) $(DEFINES_PARAMS) $(INCLUDES_PARAMS) -std=gnu11 -ffreestanding -O2 $(WARNING_FLAGS)

CXX := $(ARCH)-g++
CXX_FLAGS := $(SYSROOT_FLAGS) $(DEFINES_PARAMS) $(INCLUDES_PARAMS) -std=gnu++0x -ffreestanding -O2 -fno-exceptions -fno-rtti $(WARNING_FLAGS)

LD := $(ARCH)-gcc
LD_FLAGS := $(SYSROOT_FLAGS) -fbuiltin -ffreestanding -O2 -nostdlib $(LIBS_PARAMS)

AR := $(ARCH)-ar
AR_FLAGS := 

.PHONY: subdirs sub2 $(SUBDIRS)
.SECONDARY: $(OBJECTS)

subdirs: sub2 $(SUBDIRS)
	

sub2: $(SUBDIRS_REQUIREMENTS)
	@echo g

$(SUBDIRS):
	$(MAKE) -C $@ all

%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o$@
	
%.o: %.s
	$(AS) $(AS_FLAGS) $< -o$@

%.o: %.cpp
	$(CXX) -c $(CXX_FLAGS) $< -o$@

%.a: $(OBJECTS)
	$(AR) rcs $@ $(OBJECTS)
	mkdir -p $(BASE_DIR)/usr/lib
	cp $@ $(BASE_DIR)/usr/lib