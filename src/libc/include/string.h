#include <stdint.h>
#include <stddef.h>

#ifndef __STRING_H__
#define __STRING_H__

size_t strlen(const char* str);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);


#endif //__STRING_H__