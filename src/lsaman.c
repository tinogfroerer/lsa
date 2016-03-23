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
 *	@author: Tino Gfroerer
 * 	@date: February 6th, 2016
 *
 *	@brief: Declared functions print out licensing and app. info
 */

#include <stdio.h>

#include "lsaman.h"

void print_GPL()
{
	printf("\n");
	puts("lsa:  Copyright (C) 2016  Tino Gfroerer");
	puts("This program comes with ABSOLUTELY NO WARRANTY;"
			 " for details use `./lsa -w'.");
	puts("This is free software, and you are welcome to "
			 "redistribute it under certain conditions;"
			 " type `./lsa -c' for details.");
	printf("\n");
}

void print_man()
{
	puts("lsa: Calculates logical functions\n");
	puts("Options");
	puts("-i for only minterms");
	puts("-a for only maxterms");
	puts("-b for both");
	puts("-? for info");
}

void print_warranty()
{
	puts("For warranty information:");
	puts("Read sections 15-17 in the LICENSE or");
	puts("download the GPL v3.0 license from:");
	puts("http://www.gnu.org/licenses/gpl-3.0.txt");
}

void print_conditions()
{
	puts("For redistribution conditions:");
	puts("Read at least sections 2-6 in the LICENSE or");
	puts("download the GPL v3.0 license from:");
	puts("http://www.gnu.org/licenses/gpl-3.0.txt");
}

void print_version(const char *version) {
	puts("lsa:  Copyright (C) 2016  Tino Gfroerer");
	printf("Version: %s\n", version);
}
