
include ../common.mk

OBJECTS = string.o

INCLUDE_DIRS = include/
	
all: libc.a
	
libc.a: $(OBJECTS)
	$(AR) rcs $@ $<
	mkdir -p $(BASE_DIR)/usr/lib
	cp libc.a $(BASE_DIR)/usr/lib