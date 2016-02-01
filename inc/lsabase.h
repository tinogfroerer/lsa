#ifndef LSABASE_H
#define LSABASE_H

typedef enum {
	ZERO = 0,
	ONE = 1,
	DONTCARE = 2,
	USED = 4
} states;

// Sets all fields from begin to (end - 1) zero
void zero_array(char *begin, const char const *end);

#endif /* LSABASE_H */
