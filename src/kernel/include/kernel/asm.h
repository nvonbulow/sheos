#include <stdint.h>
#include <cpuid.h>
#include <stdbool.h>

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

//cpuid EAX == 1
//results in EDX
#define CPUID_FEATURE_FLAG_FPU  (1<<0)
#define CPUID_FEATURE_FLAG_VME  (1<<1)
#define CPUID_FEATURE_FLAG_DBE  (1<<2)
#define CPUID_FEATURE_FLAG_PSE  (1<<3)
#define CPUID_FEATURE_FLAG_TSC  (1<<4)
#define CPUID_FEATURE_FLAG_MSR  (1<<5)
#define CPUID_FEATURE_FLAG_PAE  (1<<6)
#define CPUID_FEATURE_FLAG_MCE  (1<<7)
#define CPUID_FEATURE_FLAG_CX8  (1<<8)
#define CPUID_FEATURE_FLAG_APIC (1<<9)
#define CPUID_FEATURE_FLAG__    (1<<10)
#define CPUID_FEATURE_FLAG_SEP  (1<<11)
#define CPUID_FEATURE_FLAG_MTRR (1<<12)
#define CPUID_FEATURE_FLAG_PGE  (1<<13)
#define CPUID_FEATURE_FLAG_MCA  (1<<14)
#define CPUID_FEATURE_FLAG_CMOV (1<<15)
#define CPUID_FEATURE_FLAG_PAT  (1<<16)
#define CPUID_FEATURE_FLAG_PSE  (1<<17)
#define CPUID_FEATURE_FLAG_PSN  (1<<18)
#define CPUID_FEATURE_FLAG_CLFL (1<<19)
#define CPUID_FEATURE_FLAG___   (1<<20)
#define CPUID_FEATURE_FLAG_DS   (1<<21)
#define CPUID_FEATURE_FLAG_ACPI (1<<22)
#define CPUID_FEATURE_FLAG_MMX  (1<<23)
#define CPUID_FEATURE_FLAG_FXSR (1<<24)
#define CPUID_FEATURE_FLAG_SSE  (1<<25)
#define CPUID_FEATURE_FLAG_SSE2 (1<<26)
#define CPUID_FEATURE_FLAG_SS   (1<<27)
#define CPUID_FEATURE_FLAG_HTT  (1<<28)
#define CPUID_FEATURE_FLAG_TM   (1<<29)
#define CPUID_FEATURE_FLAG_IA64 (1<<30)
#define CPUID_FEATURE_FLAG_PBE  (1<<31)

static inline bool _cpu_has_feature(uint32_t feature, bool edx) {
    unsigned int a, b, c, d;
    __get_cpuid(1, &a, &b, &c, &d);
    return d & feature;
}

static inline bool _msr_supported() {
    return _cpu_has_feature(CPUID_FEATURE_FLAG_MSR, true);
}

static inline void _get_msr(uint32_t msr, uint32_t *low, uint32_t *high) {
    asm volatile(
        "rdmsr" :
        "=a"(*low), "=d"(*high) :
        "c"(msr)
    );
}

static inline void _set_msr(uint32_t msr, uint32_t low, uint32_t high) {
    asm volatile(
        "wrmsr" : :
        "a"(low), "d"(high), "c"(msr)
    );
}

#endif //__KERNEL_ASM_H__