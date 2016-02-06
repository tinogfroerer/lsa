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
 * @brief: The print_function prints logical functions.
 *
 * Contact me: 'tino.gfroerer@gmail.com'
 */

#ifndef LSAPRINT_H
#define LSAPRINT_H

#include "lsabase.h"

typedef enum {
	minterm=0,
	maxterm=1
} whatterm;

void print_function(plane *p, const whatterm term, const int bits);

#endif /* LSAPRINT_H */
