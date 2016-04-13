
AS := $(ARCH)-as
AS_FLAGS := 

INCLUDE_FILES = $(shell find "$(BASE_DIR)/usr/include" -name "*.h" -type f -print0)

DEFINES := __IKERNEL__
DEFINES_PARAMS = $(foreach d, $(DEFINES), -D$d)

LIBS := gcc
LIBS_PARAMS = $(foreach d, $(LIBS), -l$d)

SYSROOT_FLAGS = --sysroot="$(BASE_DIR)" -isystem=/usr/include

CC := $(ARCH)-gcc
CC_FLAGS = $(SYSROOT_FLAGS) $(DEFINES_PARAMS) -std=gnu99 -ffreestanding -O2 -Wall -Wextra

CXX := $(ARCH)-g++
CXX_FLAGS = $(SYSROOT_FLAGS) $(DEFINES_PARAMS) -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

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