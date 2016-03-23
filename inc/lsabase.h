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
 * @brief: Defines types and functions used in various sections of lsa
 *
 * Contact me: 'tino.gfroerer@gmail.com'
 */

#ifndef LSABASE_H
#define LSABASE_H

typedef enum {
	ZERO = 0,
	ONE = 1,
	DONTCARE = 2,
	USED = 4
} states;

typedef struct plane {
	char *psingle; // A single plane
	struct plane *next;
} plane;

typedef enum {
	none,
	only_minterm,
	only_maxterm,
	both,
	warranty,
	conditions,
	version
} dowhat;

// Sets all fields from begin to (end - 1) zero
void zero_array(char *begin, const char const *end);

/*
 * @brief: How many $(param)s there are in $(ar)
 */
int amount_in_ar(const char *ar, const int bits, \
												 const char param);

#endif /* LSABASE_H */
