/*
 * @brief: This file generates input for lsa
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	srand(time(NULL));
	if (argc == 2) {
		int bits = atoi(argv[1]);
		int times = 1 << bits;
		int i;
		for (i = 0; i < times; i++) {
			printf("%d", rand() % 3);
		}
	}
	
	return 0;
}
