
#ifndef __STDIO_H__
#define __STDIO_H__

#ifdef __cplusplus
extern "C" {
#endif
    
void putchar(const char);

void puts(const char*);

int printf(const char* __restrict, ...);

void print(const char*);

#ifdef __cplusplus
}
#endif

#endif //__STDIO_H__