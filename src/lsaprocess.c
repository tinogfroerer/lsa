#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lsabase.h"
#include "lsaprocess.h"
#include "log2xorseq.h"

/* Here for debugging purposes 
static void printplane (const char *pmask, const int bits)
{
	
	int i;
	for (i = 0; i < bits; i++) {
		int nr;
		nr = (int)pmask[i];
		printf("%d", nr);
	}
	printf("\n");
} */

// @return: Returns 1 if neither don't care or used flags are set
static int check_care(char c)
{
	return (int)!(c & (DONTCARE | USED));
}

// @return: Returns 1 if element at dbelement is = id or DONTCARE
char check_element (const char c, const char id)
{
	if ((c & DONTCARE) || (c == id)) return 1;
	return 0; // else
}

// Sets a mask of $(bits) chars to the count hexmap
// count=0b101 will give basemask[0] = 1; basemask[1] = 0; ..[2] = 1;
static void init_mask(char *basemask, const unsigned int bitmap, \
							 				const int bits)
{
	int i;
	for (i = 0; i < bits; i++) {
		basemask[i] = (char)!!(bitmap & (1 << i)); // Will be 0 or 1
	}
}

/*
 * @brief: How many $(param)s there are in $(ar)
 */
static int amount_in_ar(const char *ar, const int bits, \
												 const char param)
{
	int counter = 0;
	const char* const end = ar + bits;
	for (; ar < end; ar++) {
		if (*ar == param) counter++;
	}
	return counter;
}

/*
 * @brief: Returns a mask as bitmap, deduced from basemask
 * @param: const char *basemask: The basemask with $(bits) elements
 * @param: const int bits: How many input bits are used
 * @return: A bitfield, where for every 1 in basemask there is a 1 \
 * 					in that position
 */
static unsigned int get_const_mask(const char *basemask, \
																	 const int bits)
{
	const char* const end = basemask + bits;
	unsigned int curbit = 1; // Exponential counter
	// Bitmap is the const address part from basemask
	unsigned int bitmap = 0;
	
	for (; basemask < end; basemask++, curbit<<=1) {
		if (*basemask == 1) bitmap |= curbit;
	}
	
	return bitmap;
}

/*
 * @description: 
 * Returns a mask as bitmap, where for the smallest $(bp) twos,
 * the mask is xored on those position. Starting for mask is 0.
 * @param: const char *basemask: The basemask with $(bits) elements
 * @param: const int bits: How many input bits are used
 * @param: const bp: Specifies at which two one should halt (breakpnt)
 * @return: the mask as a 32bit bitfield
 */
static unsigned int get_var_mask(const char *basemask, \
																 const int bits, const int bp)
{
	const char* const end = basemask + bits;
	unsigned int curbit = 1; // exponential counter
	unsigned int var_mask = 0;
	int count2s = 0;
	for (; basemask < end; basemask++, curbit<<=1) {
		if (*basemask == 2) {
			count2s++;
			var_mask |= curbit;
			if (count2s == bp) return var_mask;
		}
	}
	
	assert(0); // There must be at least bp 2s in the basemask
}

/*
 * @description:
 * Checks if a mask, portraying a plane, is correct.
 * Correct in this context means, that all members of the plane
 * bitwise are DONTCARE or == id
 */
static char check_mask(const char *db, const char *basemask, \
											 const int id, const int bits)
{
	// Nr of free axis
	unsigned int n_dc = amount_in_ar(basemask, bits, 2);
	unsigned int constmask; // A mask that is fixed
	unsigned int db_size = 1 << bits;
	
	// varmask is xored with constmask, to give address to check
	// n_dc_der is a derivate of n_dc. n_dc_der cannot be 0 =>
	unsigned int n_dc_der = (n_dc > 0) ? n_dc : 1;
	unsigned int varmask[n_dc_der]; 
	unsigned int i; // local counter
	// Make the masks
	constmask = get_const_mask(basemask, bits);
	for (i = 0; i < n_dc; i++) {
		varmask[i] = get_var_mask(basemask, bits, i + 1);
	}
	
	// Now start checking all the addresses
	unsigned int times = 1 << n_dc; // How many times the loop is exec.
	for (i = 0; i < times; i++) {
		assert(constmask < db_size); // If otherwise, out of bound db
		if (!check_element(*(db + constmask), id)) return 0;
		// Alter constmask with the right varmask
		// The right varmask is given by th log2.. func
		// Sadly, the log2xorseq(times-1) is equal to n_dc, so I have to %
		
		constmask ^= varmask[log2xorseq(i) % n_dc_der];
	}
	
	// The mask appears to be valid
	return 1;
}

/*
 * @brief: Searches for the biggest plane of $(id)'s and DONTCARES
 * @param: char *basemask: The mask where we stem from
 * @param: const int bits: How many bits the (char-)bitmask is wide
 * @param: char id: Are we looking for ONES or ZEROS
 * @param: const int c: From where up we are searching (default=0)
 * @return: Pointer to the biggest mask
 */
static char* get_mask(const char *db, const char *basemask, \
											const int bits, const char id, const int c)
{
	char curc; // We are checking from curc to above
	
	/* Debugging check_mask segv issue
	printf("reclvl: %d\n", c);
	printf("basemask: ");
	printplane(basemask, bits); */
	/*We were getting a stackoverflow ... */
	
	// Check the basemask. If it is wrong, return NULL
	if (check_mask(db, basemask, id, bits)) {
	// It is correct. Check the derivates
		char *dermask[bits-c]; // These are the derivates
		// The resmask is the ret of the next get_mask()
		// It is NULL if there was no good mask, or the best mask found
		char *resmask[bits-c];
		int i; // counter
		for (curc = c, i = 0; curc < bits; curc++, i++) {
			// Make the derivate mask
			dermask[i] = malloc(bits * sizeof(char)); // Derivate mask
			memcpy(dermask[i], basemask, bits * sizeof(char));
			dermask[i][curc] = 2;
			// Now feed it back to this function recursively
			resmask[i] = get_mask(db, dermask[i], bits, id, curc + 1);
		} 
		// We got all the masks we want, so free the dermasks
		// Also, check for the best resmask already
		char* bestmask = NULL;
		int bestscore = 0;
		for (i = 0; i < bits - c; i++) {
			free(dermask[i]);
			// check for the best mask
			int score = 0;
			if (resmask[i]) score = amount_in_ar(resmask[i], bits, 2);
			if (bestscore < score) {
				bestscore = score;
				// Wait a sec. This one is better, Delete the old one!
				if (bestmask) free(bestmask);
				// Now replace the dangling pointer with the new hero!
				bestmask = resmask[i];
			} else {
				// No highscore? Delete that crap!
				if (resmask[i]) free(resmask[i]);
			}
		} 
		
		/* Debugging here:
		if (bestmask && c == 0) {
			printf("At level 0: ");
			printplane(bestmask, bits);
			printf("\n");
		}
		else if (c == 0) {
			printf("At level 0: ");
			printplane(basemask, bits);
			printf("\n");
		}*/
		
		// If there is a winner mask, return it. If not, move on.
		if (bestmask) return bestmask;

		// The mask is correct, but we didn't find better masks
		char *basemask_cp = malloc(bits * sizeof(char));
		memcpy(basemask_cp, basemask, bits * sizeof(char));
		return basemask_cp;
	} /* end check_mask() */
	
	if (c == 0) assert(0); // The first basemask should never fail
	return NULL;
}

// Searches for the biggest plane of all ones (or don't cares)
// In this function itself, there are only initializers to get le mask
// The function deals with the memory issues (saves new plane)
// The real magic takes place in the recursive get_mask function
static char min_plane(plane *p, const char *db, \
											const char const *curdb, const int bits, \
											const unsigned int count)
{
	if (!(*curdb & 1)) return 0; // We're doing minterms, we need ones
	
	// There is going to be a plane, so allocate memory for it
	p->next = malloc(sizeof(plane));
	p = p->next;
	p->next = NULL;
	
	char basemask[bits];
	init_mask(basemask, count, bits);
	
	// Give us the best mask with ONES, starting at bit 0
	p->psingle = get_mask(db, basemask, bits, 1, 0); 
	
	return 1;
}

void flag_used(char *db, const char *basemask, const int bits)
{
	// Nr of free axis
	unsigned int n_dc = amount_in_ar(basemask, bits, 2);
	unsigned int constmask; // A mask that is fixed
	unsigned int db_size = 1 << bits;
	
	// varmask is xored with constmask, to give address to check
	// n_dc_der is a derivate of n_dc. n_dc_der cannot be 0 =>
	unsigned int n_dc_der = (n_dc > 0) ? n_dc : 1;
	unsigned int varmask[n_dc_der]; 
	unsigned int i; // local counter
	// Make the masks
	constmask = get_const_mask(basemask, bits);
	for (i = 0; i < n_dc; i++) {
		varmask[i] = get_var_mask(basemask, bits, i + 1);
	}
	
	// Now start flagging all the mask members used
	unsigned int times = 1 << n_dc; // How many times the loop is exec.
	for (i = 0; i < times; i++) {
		assert(constmask < db_size); // If otherwise, out of bound db
		*(db + constmask) |= USED; // Flag as used
		// Alter constmask with the right varmask
		// The right varmask is given by th log2.. func
		// Sadly, the log2xorseq(times-1) is equal to n_dc, so I have to %
		constmask ^= varmask[log2xorseq(i) % n_dc_der];
	}
}

planeparent process(char *db, const int bits, const int db_size)
{
	
	char *begin = db; // This is the start adress
	const char *end = db + db_size;
	unsigned int count = 0; // Maybe not used
	
	plane *minp = malloc(sizeof(plane));
	plane *maxp = malloc(sizeof(plane));
	minp->psingle = NULL;
	maxp->psingle = NULL;
	minp->next = NULL;
	maxp->next = NULL;
	plane *curmin = minp; // Pointers to the youngest minp child
	// plane *curmax = maxp; 
	planeparent parent;
	
	for (count = 0; db < end; db++, count++) {
		char minflag;
		
		if(!check_care(*db)) continue; // If used or don't care are set
		
		#if DEBUG == 1
		printf("Element: %x\n", count);
		#endif
		
		minflag = min_plane(curmin, begin, db, bits, count);
		// max_plane(curmax, begin, db, bits);
		// tbi: set newest plane members as used
		// Right now, this tells the prgrm to break after first plane
		if (minflag) {
			// There is a new element, so go to that element
			curmin = curmin->next;
			// Flag everything matching to the new plane as used
			flag_used(begin, curmin->psingle, bits);
		} 
	}
	
	// Yey, we are done processing.
	// Now skip the first elements of minp and maxp, they're useless
	plane *obsolete_p = minp;
	minp = minp->next;
	free(obsolete_p);
	// maxp not implemented yet, so just free it, will ya
	free(maxp);
	maxp = NULL;
	
	// Now this is what we return
	parent.minp = minp;
	parent.maxp = maxp;
	
	return parent;
}
