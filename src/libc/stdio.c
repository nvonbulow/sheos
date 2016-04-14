#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifdef __IKERNEL__
#include <kernel/tty.h>
#endif

void putchar(const char c) {
#ifdef __IKERNEL__

	tty_putchar(c);

#else //__IKERNEL__

#endif //__IKERNEL__
}

void puts(const char* str) {
#ifdef __IKERNEL__

	tty_puts(str);

#else //__IKERNEL__

#endif //__IKERNEL__
}

void print(const char* str, size_t length) {
	for(size_t i = 0; i < length; i++) {
		putchar(str[i]);
	}
}

int printf(const char* __restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);
 
	int written = 0;
	size_t amount;
	bool rejected_bad_specifier = false;
 
	while(*format != '\0') {
		if(*format != '%') {
		print_c:
			amount = 1;
			while (format[amount] && format[amount] != '%') {
				amount++;
			}
			print(format, amount);
			format += amount;
			written += amount;
			continue;
		}
 
		const char* format_begun_at = format;
 
		if (*(++format) == '%') {
			goto print_c;
		}
 
		if (rejected_bad_specifier) {
		incomprehensible_conversion:
			rejected_bad_specifier = true;
			format = format_begun_at;
			goto print_c;
		}
 
		if(*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			print(&c, sizeof(c));
		}
		else if (*format == 's') {
			format++;
			const char* s = va_arg(parameters, const char*);
			print(s, strlen(s));
		}
		else if(*format == 'i' || *format == 'd') {
			format++;
			int i = va_arg(parameters, int);
			char i2str[17];
			itoa(i, i2str, 10);
			print(i2str, strlen(i2str));
		}
		else {
			goto incomprehensible_conversion;
		}
	}
 
	va_end(parameters);
 
	return written;
}