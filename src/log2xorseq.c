#include <stdio.h>

#include "log2xorseq.h"

static unsigned int discreet_log2(unsigned int val)
{
	unsigned int log = 0;
	while (val >>= 1) log++;
	return log;
}

// Returns the pos element of the sequence: 0,1,0,2,0,1,0,3,0,1,0,2...
unsigned int log2xorseq(unsigned int pos)
{	
	return discreet_log2(((pos) ^ (pos + 1)) + 1) - 1;
}

