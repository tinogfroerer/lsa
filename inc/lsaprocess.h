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
