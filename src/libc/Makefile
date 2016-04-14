
include ../common.mk

OBJECTS = string.o stdio.o stdlib.o

INCLUDE_DIRS = include/
	
all: libc.a
	
libc.a: $(OBJECTS)
	$(AR) rcs $@ $(OBJECTS)
	mkdir -p $(BASE_DIR)/usr/lib
	cp libc.a $(BASE_DIR)/usr/lib