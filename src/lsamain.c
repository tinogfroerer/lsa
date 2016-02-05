/*
 *  lsa: Creates logical functions
 *  Copyright (C) 2016 Tino Gfroerer
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
 * v0.4: outputting functional
 * v0.5: maxterms working
 * v1.0: working, but only slightly tested
 * v1.1: alter mask processing to ensure better visibilty
 * 
 * @version: 0.4
 */

#include <stdio.h>
#include <stdlib.h>

#include "lsabase.h"
#include "lsaread.h"
#include "lsaprocess.h"
#include "lsaprint.h"

#define MAX_BITS 16

const int max_bits = MAX_BITS;
const int max_db_size = 1 << MAX_BITS; // Acessable with 16bit address

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
	
	// This here processes the input to masks
	planeparent pp = process(db, bits, db_size);
	// Extract the minterms, (maxterms are TBI)
	plane *minp = pp.minp;
	
	// If there are no minterms...
	if(minp == NULL) return 0;
	
	// Print the minterms
	print_function(minp, minterm, bits);
	
	// Now clean up the memory
	do {
		plane *next = minp->next;
		free(minp->psingle);
		free(minp);
		minp = next;
	} while (minp);
	
	return 0;
}
