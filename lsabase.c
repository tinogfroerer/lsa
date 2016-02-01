#include <stdio.h>

#include "inc/lsabase.h"

void zero_array(char *begin, const char const *end)
{
	char *array = begin;
	
	for (array = begin; array < end; array++) {
		*array = 0;
	}
	
}


