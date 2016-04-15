
AS := $(ARCH)-as
AS_FLAGS := -I$(BASE_DIR)/multiboot

INCLUDE_FILES = $(shell find "$(BASE_DIR)/usr/include" -name "*.h" -type f -print0)

DEFINES := __IKERNEL__
DEFINES_PARAMS = $(foreach d, $(DEFINES), -D$d)

LIBS := gcc
LIBS_PARAMS = $(foreach d, $(LIBS), -l$d)

SYSROOT_FLAGS = --sysroot="$(BASE_DIR)" -isystem=/usr/include

WARNING_FLAGS = -Wno-write-strings -Wall -Wextra

CC := $(ARCH)-gcc
CC_FLAGS = $(SYSROOT_FLAGS) $(DEFINES_PARAMS) -std=gnu99 -ffreestanding -O2 $(WARNING_FLAGS)

CXX := $(ARCH)-g++
CXX_FLAGS = $(SYSROOT_FLAGS) $(DEFINES_PARAMS) -std=c++0x -ffreestanding -O2 -fno-exceptions -fno-rtti $(WARNING_FLAGS)

LD := $(ARCH)-gcc
LD_FLAGS = $(SYSROOT_FLAGS) -fbuiltin -ffreestanding -O2 -nostdlib -fno-use-linker-plugin $(LIBS_PARAMS)

AR := $(ARCH)-ar
AR_FLAGS = 

%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o$@
	
%.o: %.s
	$(AS) $(AS_FLAGS) $< -o$@

%.o: %.cpp
	$(CXX) -c $(CXX_FLAGS) $< -o$@