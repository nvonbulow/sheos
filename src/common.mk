SYSROOT_INCLUDE_FILES = $(shell find "$(BASE_DIR)/usr/include" -name "*.h" -type f -print)

DEFINES := __IKERNEL__
DEFINES_PARAMS = $(foreach d, $(DEFINES), -D$d)

DEBUG_PARAMS = -ggdb

LIBS += gcc
LIBS_PARAMS = $(foreach d, $(LIBS), -l$d)

INCLUDES := "$(BASE_DIR)/multiboot" "$(BASE_DIR)/usr/include"
INCLUDES_PARAMS = $(foreach d, $(INCLUDES), -I$d)

# For some reason, using sysroot with g++ causes problems with nested namespaces
# Just use it with the linker so it can find the libraries
SYSROOT_FLAGS = --sysroot="$(BASE_DIR)" -isystem=/usr/include

WARNING_FLAGS = -Wno-write-strings -Wall -Wextra

SUBDIRS = $(shell find . -mindepth 2 -maxdepth 2 -name Makefile -printf "%h\n" | uniq)

AS := $(ARCH)-as
AS_FLAGS := -I$(BASE_DIR)/multiboot $(DEBUG_PARAMS)

x86_64_FLAGS = -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fpic
i686_FLAGS = -fpic

CC := $(ARCH)-gcc
CC_FLAGS := $(DEFINES_PARAMS) $(INCLUDES_PARAMS) $($(PLATFORM)_FLAGS) -std=gnu11 -ffreestanding -O2 $(WARNING_FLAGS) $(DEBUG_PARAMS)

CXX := $(ARCH)-g++
CXX_FLAGS := $(DEFINES_PARAMS) $(INCLUDES_PARAMS) $($(PLATFORM)_FLAGS) -std=gnu++11 -ffreestanding -O2 -fno-exceptions -fno-rtti $(WARNING_FLAGS) $(DEBUG_PARAMS)

LD := $(ARCH)-gcc
LD_FLAGS := $(SYSROOT_FLAGS) -fbuiltin -ffreestanding -O2 -nostdlib $(LIBS_PARAMS)
	
CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:= $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRT_OBJS := $(CRTBEGIN_OBJ) $(CRTEND_OBJ)

AR := $(ARCH)-ar
AR_FLAGS := 

.PHONY: subdirs sub2 $(SUBDIRS)
.SECONDARY: $(OBJECTS)

subdirs: sub2 $(SUBDIRS)
	

sub2: $(SUBDIRS_REQUIREMENTS)
	

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