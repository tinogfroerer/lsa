/*
 * @author: Tino Gfroerer
 * @date: February 2nd, 2016
 *
 * @description:
 * This is the main source file to calculate boolean functions
 * This program can calculate boolean functions with up to
 * sixteen input-bits.
 * Any version below 1.0 is not functional yet:
 * v0.1: database functional
 * v0.2: minterms working
 * v0.3 minterms optimal
 * v0.4: alter mask processing to ensure better visibilty
 * v0.5: maxterms working
 * v0.6: outputting functional
 * v1.0: working, but only slightly tested
 * 
 * @version: 0.3
 */

#include <stdio.h>
#include <stdlib.h>

#include "lsabase.h"
#include "lsaread.h"
#include "lsaprocess.h"

#define MAX_BITS 16

const int max_bits = MAX_BITS;
const int max_db_size = 1 << MAX_BITS; // Acessable with 16bit address

/* Here for debugging purposes
void printdb (const char *db, const char const *end)
{
	for (; db < end; db++) {
		int d = (int)(*db);
		printf("%i", d);
	}
	printf("\n");
}
*/

/* Here for debugging purposes */
void printplane (const char *pmask, const int bits)
{
	
	int i;
	for (i = 0; i < bits; i++) {
		int nr;
		nr = (int)pmask[i];
		printf("%d", nr);
	}
	printf("\n");
}

int main ()
{
	char db[max_db_size]; // The main database
	int bits = 0; // The amount of input bits used
	int db_size = 0;
	
	zero_array(db, db + max_db_size); // Sets elements in the array zero
	
	bits = read_in(db, max_bits);
	db_size = 1 << bits;
	
	switch (bits) {
	case READERROR:
		fprintf(stderr, "Error while reading input!\n");
		return 1;
	case READOVERFLOW:
		fprintf(stderr, "Too much input."
			"Can process only %i input-bits!\n", max_bits);
		return 1;
	case 0:
		fprintf(stderr, "Seriously?\n");
		return 1;
	default:
		;
	} 
	
	planeparent pp = process(db, bits, db_size);
	plane *minp = pp.minp;
	
	if(minp == NULL) return 0; // If there are no planes...
	// Now comes the printing part
	do {
		char *pmask = minp->psingle;
		printplane(pmask, bits);
		// Now, make valgrind happy, will ya
		plane *next = minp->next;
		free(minp->psingle);
		free(minp);
		minp = next;
	} while (minp);
	
	return 0;
}
