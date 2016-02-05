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

void zero_array(char *begin, const char const *end)
{
	char *array = begin;
	
	for (array = begin; array < end; array++) {
		*array = 0;
	}
	
}

int amount_in_ar(const char *ar, const int bits, \
												 const char param)
{
	int counter = 0;
	const char* const end = ar + bits;
	for (; ar < end; ar++) {
		if (*ar == param) counter++;
	}
	return counter;
}

