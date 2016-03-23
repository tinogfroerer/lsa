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
 * 
 * @version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "lsabase.h"
#include "lsaread.h"
#include "lsaprocess.h"
#include "lsaprint.h"
#include "lsaman.h"

#define MAX_BITS 16

const char *VERSION = "1.0";

const int max_bits = MAX_BITS;
const int max_db_size = 1 << MAX_BITS; // Acessable with 16bit address

// Works with cmdline options
// Use following after this function exits:
// 	argc -= optind;
//	argv += optind;
dowhat cmdopt(int argc, char **argv) 
{
	dowhat todo = none;
	char ch;
	while((ch = getopt(argc, argv, "iabwc?v")) != EOF)
		switch (ch) {
		case 'i':
			todo = only_minterm;
			break;
		case 'a':
			todo = only_maxterm;
			break;
		case 'b':
			todo = both;
			break;
		case 'c':
			todo = conditions;
			break;
		case 'w':
			todo = warranty;
			break;
		case 'v':
			todo = version;
			break;
		default: // Display GNU info	
			;
		}
		
	return todo;
}

int main (int argc, char **argv)
{
	char db[max_db_size]; // The main database
	int bits = 0; // The amount of input bits used
	int db_size = 0;
	
	// Are we gonna do minterms, maxterms or both?
	dowhat todo = cmdopt(argc, argv);
	argc -= optind;
	argv += optind;
	if (todo == warranty) {
		print_warranty();
		return 0;
	} else if (todo == conditions) {
		print_conditions();
		return 0;
	} else if (todo == version) {
		print_version(VERSION);
		return 0;
	}
	else if (todo == none) {
		print_GPL();
		print_man();
		return 0;
	} // else process
	
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
	
	// If there are no 0/1 print y=1/y=0 and exit
	int ones_in_db = amount_in_ar(db, db_size, (char)1);
	int zeros_in_db = amount_in_ar(db, db_size, (char)0);
	if (zeros_in_db == 0) {
		printf("y =\n1\n");
		return 0;
	} else if (ones_in_db == 0) {
		printf("y =\n0\n");
		return 0;
	}
	
	// This here processes the input to masks
	planeparent pp = process(db, bits, db_size, todo);
	// Extract the minterms, (maxterms are TBI)
	plane *minp = pp.minp;
	plane *maxp = pp.maxp;
	
	// If there are no terms
	if (minp == NULL && maxp == NULL) return 0;
	
	// Print the minterms
	if (todo == only_minterm || todo == both)
		print_function(minp, minterm, bits);
	if (todo == only_maxterm || todo == both)
		print_function(maxp, maxterm, bits);
	
	// Now clean up the memory
	while (minp) {
		plane *next = minp->next;
		free(minp->psingle);
		free(minp);
		minp = next;
	}
	
	while (maxp) {
		plane *next = maxp->next;
		free(maxp->psingle);
		free(maxp);
		maxp = next;
	}
	
	return 0;
}
