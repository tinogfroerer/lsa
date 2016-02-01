#ifndef LSAREAD_H
#define LSAREAD_H

#define READOVERFLOW 254
#define READERROR 255

/*
 * @brief: Reads input from stdio to database
 */
int read_in(char *db, const int max_bits);

#endif /* LSAREAD_H */
