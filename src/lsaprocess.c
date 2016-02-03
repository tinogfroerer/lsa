#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lsabase.h"
#include "lsaprocess.h"
#include "log2xorseq.h"

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
	int n_dc = amount_in_ar(basemask, bits, 2); // Nr of free axis
	unsigned int constmask; // A mask that is fixed
	int db_size = 1 << bits;
	
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
 * @brief: Searches for the biggest plain of $(id)'s and DONTCARES
 * @param: char *basemask: The mask where we stem from
 * @param: const int bits: How many bits the (char-)bitmask is wide
 * @param: char id: Are we looking for ONES or ZEROS
 * @param: const int c: From where up we are searching (default=0)
 * @return: Pointer to the biggest mask
 */
static char* get_mask(const char *db, char *basemask, \
											const int bits, const char id, const int c)
{
	char curc; // We are checking from curc to above
	
	// Check the basemask. If it is wrong, return NULL
	if (check_mask(db, basemask, id, bits)) {
	// It is correct. Check the derivates
		/*
		for (curc = c; curc < bits; curc++) {
		char *dermask = malloc(bits * sizeof(char)); // Derivate mask
		} */
	} 
		
	return NULL;
}

// Searches for the biggest plain of all ones (or don't cares)
// In this function itself, there are only initializers to get le mask
// The function deals with the memory issues (saves new plane)
// The real magic takes place in the recursive get_mask function
static char min_plane(plain *p, const char *db, \
											const char *curdb, const int bits, \
											const unsigned int count)
{
	if (!(*curdb & 1)) return 0; // We're doing minterms, we need ones
	
	// There is going to be a plain, so allocate memory for it
	p->next = malloc(sizeof(plain));
	p = p->next;
	p->next = NULL;
	
	char basemask[bits];
	init_mask(basemask, count, bits);
	
	// Give us the best mask with ONES, starting at bit 0
	p->psingle = get_mask(db, basemask, bits, 1, 0); 
	
	return 1;
}

plainparent process(char *db, const int bits, const int db_size)
{
	
	const char *begin = db; // This is the start adress
	const char *end = db + db_size;
	unsigned int count = 0; // Maybe not used
	
	plain *minp = malloc(sizeof(plain));
	plain *maxp = malloc(sizeof(plain));
	minp->psingle = NULL;
	maxp->psingle = NULL;
	minp->next = NULL;
	maxp->next = NULL;
	plain *curmin = minp; // Pointers to the youngest minp child
	plain *curmax = maxp; 
	plainparent parent = {minp, maxp};
	
	for (count = 0; db < end; db++, count++) {
		char minflag;
		
		if(!check_care(*db)) continue; // If used or don't care are set
		
		#if DEBUG == 1
		printf("Element: %x\n", count);
		#endif
		
		minflag = min_plane(curmin, begin, db, bits, count);
		// max_plane(curmax, begin, db, bits);
		// tbi: set newest plain members as used
		if (minflag);
	}
	
	return parent;
}
