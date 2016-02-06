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

/* Contact me: 'tino.gfroerer@gmail.com' */

#ifndef LSAREAD_H
#define LSAREAD_H

#define READOVERFLOW 254
#define READERROR 255

/*
 * @brief: Reads input from stdio to database
 */
int read_in(char *db, const int max_bits);

#endif /* LSAREAD_H */
