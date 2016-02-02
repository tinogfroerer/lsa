#include <stdio.h>
#include <stdlib.h>

#include "lsabase.h"
#include "lsaprocess.h"

// @return: Returns 1 if neither don't care or used flags are set
int check_care(char c)
{
	return (int)!(c & (DONTCARE | USED));
}

// Searches for the biggest plain of all ones (or don't cares)
int min_plane(plain *p, const char* const begin, char *db, \
							const int bits, const unsigned int count)
{
	if (!(*db & 1)) return 0; // We're doing minterms, we need ones
	
	return 0;
}

plainparent process(char *db, const int bits, const int db_size)
{
	
	const char *begin = db; // This is the start adress
	const char *end = db + db_size;
	unsigned int count = 0; // Maybe not used
	
	plain *minp = malloc(sizeof(plain));
	plain *maxp = malloc(sizeof(plain));
	minp->psingle = NULL;
	maxp->psingle = NULL;
	minp->next = NULL;
	maxp->next = NULL;
	plain *curmin = minp; // Pointers to the youngest minp child
	plain *curmax = maxp; 
	plainparent parent = {minp, maxp};
	
	for (count = 0; db < end; db++, count++) {
		if(!check_care(*db)) continue; // If used or don't care are set
		
		min_plane(curmin, begin, db, bits, count);
		// max_plane(curmax, begin, db, bits);
		
	}
	
	return parent;
}
