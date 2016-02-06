// This file generates all digits with $(bits) input

#include <stdio.h>
#include <assert.h>

//#define TERNARY

#ifndef TERNARY
#define BINARY
#endif

unsigned int ipow(unsigned int base, unsigned int exp)
{
    unsigned int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

void print_base(unsigned int nr, const int digits, \
								const unsigned int base)
{
	char str[digits + 1];
	str[digits] = '\0';
	
	int i;
	for (i = digits - 1; nr != 0; i--) {
		str[i] = (nr % base) + '0';
		nr /= base;
	}
	
	for (; i >= 0; i--) {
		//printf("i=%u\n", i);
		str[i] = '0';
	} 
	
	printf("%s\n", str);
}

int main(int argc, char **argv)
{
	unsigned int bits = 2;
	if (argc == 2) {
		int pbits = 0;
		pbits = atoi(argv[1]);
		if (pbits < 1){
			fprintf(stderr, "Are you kidding me?\n");	
			return 1;
		}
		bits = (unsigned int)pbits;
	
	} else if (argc > 2) {
		fprintf(stderr, "Too many arguments");
	}
	
	const int digits = ipow(2, bits);
	// digits with DCs
	unsigned int c_wdontcare = ipow(3, digits);
	unsigned int c_wbinary = ipow(2, digits);
	
	unsigned int i;
	
	#ifdef TERNARY
	for (i = 0; i < c_wdontcare; i++) {
		print_base(i, digits, 3);
	}
	#endif
	#ifdef BINARY
	for (i = 0; i < c_wbinary; i++) {
		print_base(i, digits, 2);
	}
	#endif
	
	
	
	return 0;
}
