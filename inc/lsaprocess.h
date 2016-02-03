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

typedef struct plain {
	char *psingle; // A single plane
	struct plain *next;
} plain;

typedef struct {
	plain *maxp;
	plain *minp;
} plainparent;

/*
 * @brief: The parent function. Only calls other functions
 */
plainparent process(char *db, const int bits, const int db_size);

#endif /* LSAPROCESS_H */
