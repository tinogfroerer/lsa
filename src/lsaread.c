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

#include <stdio.h>

#include "lsabase.h"
#include "lsaread.h"

int read_in(char *db, const int max_bits)
{
	int i = 0; // counter
	int mask = 1; // used to see how many input bits are used
	int log2 = 0; // same as mask
	char c; // Char buffer
	char binary; // The number in c, or else error
	int max_counter = (1 << max_bits) - 1;
	
	for (i = 0; (c = getc(stdin) ) != EOF; i++, db++) {
		if (i > max_counter) return READOVERFLOW;
		if (c == '\n') {
			#if DEBUG == 1
			printf("Pressed enter\n");
			#endif
			break; // Enter terminates us too
		}
		
		binary = c - '0'; // make it a one or zero, otherwise fault
		if (binary > DONTCARE) return READERROR;
			*db = binary; // If correct, write it
	}
	
	#if DEBUG == 1
	printf("Made it out\n"
		"i = %d\n", i);
	#endif
	// See how many input bits were used
	for (log2 = 0; i > mask; mask <<= 1, log2++);
	
	if (i != mask) return READERROR;
	
	return log2; 
}
