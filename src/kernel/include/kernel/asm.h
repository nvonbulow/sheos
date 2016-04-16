#include <stdint.h>

#ifndef __KERNEL_ASM_H__
#define __KERNEL_ASM_H__

static inline void _outb(uint16_t port, uint8_t value) {
	asm volatile(
		"outb %0, %1" : :
		"a"(value), "Nd"(port)
	);
}

static inline uint8_t _inb(uint16_t port) {
	uint8_t value;
	asm volatile(
		"inb %1, %0" :
		"=a"(value) :
		"Nd"(port)
	);
	return value;
}

static inline void _outw(uint16_t port, uint16_t value) {
	asm volatile(
		"outw %0, %1" : :
		"a"(value), "Nd"(port)
	);
}

static inline uint16_t _inw(uint16_t port) {
	uint16_t value;
	asm volatile(
		"inw %1, %0" :
		"=a"(value) :
		"Nd"(port)
	);
	return value;
}

static inline void _outl(uint16_t port, uint32_t value) {
	asm volatile(
		"outl %0, %1" : :
		"a"(value), "Nd"(port)
	);
}

static inline uint32_t _inl(uint16_t port) {
	uint32_t value;
	asm volatile(
		"inl %1, %0" :
		"=a"(value) :
		"Nd"(port)
	);
	return value;
}

#endif //__KERNEL_ASM_H__