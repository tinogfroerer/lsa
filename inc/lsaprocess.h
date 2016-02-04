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
 * @brief:
 * This file contains the declarations for all functions processing
 * the bitfield database, in order to get a function output.
 */

#ifndef LSAPROCESS_H
#define LSAPROCESS_H

typedef struct plane {
	char *psingle; // A single plane
	struct plane *next;
} plane;

typedef struct {
	plane *maxp;
	plane *minp;
} planeparent;

/*
 * @brief: The parent function. Only calls other functions
 */
planeparent process(char *db, const int bits, const int db_size);

#endif /* LSAPROCESS_H */
