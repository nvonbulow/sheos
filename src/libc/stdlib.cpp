#include <stdlib.h>
#include <stdio.h>

char* itoa(int value, char* str, int radix) {
	char sign = 0;
	unsigned int digit;
	char temp[17];
	int temp_loc = 0;
	int str_loc = 0;

	if(radix == 10 && value < 0) {
		sign = 1;
		value = -value;
	}

	do {
		digit = (unsigned int) value % radix;
		if(digit < 10) {
			temp[temp_loc++] = '0' + digit;
		}
		else {
			temp[temp_loc++] = 'A' + digit - 10;
		}
		value = (((unsigned int) value) / radix);
	} while((unsigned int) value > 0);

	//add the negative sign if nessecary
	if(radix == 10 && sign) {
		temp[temp_loc] = '-';
	}
	else {
		temp_loc--;
	}

	//The string is now reversed. We need to reverse it now
	while(temp_loc >= 0) {
		str[str_loc++] = temp[temp_loc--];
	}

	//Null-terminate the string
	str[str_loc] = 0;
	return str;
}