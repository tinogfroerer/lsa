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
 * @date: February 5th, 2016
 * @brief: The print_function prints min- & max-terms
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "lsabase.h"
#include "lsaprint.h"

void print_function(plane *p, const whatterm term, const int bits)
{
	// The little_op char is added between variables in a single minterm
	// The big_op is added at the end
	char little_op, big_op;
	
	char invert;
	if (term == minterm) {
		little_op = '*';
		big_op = '+';
	} else if (term == maxterm) {
		little_op = '+';
		big_op = '*';
	} else {
		return; // Invalid term
	}
	
	puts("y =");
	
	while (p) { // p advancement is in the middle
		const char *end = p->psingle;
		// The MSB is at the end
		const char *mask = p->psingle + bits - 1;
		
		// Open bracket
		printf("(");
		
		int i;
		for (i = 1; mask >= end; mask--, i++) {
			// Skip dontcares
			if (*mask == 2) continue;
			
			if (*mask == (char)term) {
				printf("¬");
			}
			
			printf("x%d", i);
			if (mask > end) {
				printf(" %c ", little_op);
			}
		} 
		
		p = p->next; // Advance
		
		// Close brackets and trail with big_op & \n
		printf(")");
		if (p) {
			printf(" %c\n", big_op);
		}
	}
	
	printf("\n");
}
