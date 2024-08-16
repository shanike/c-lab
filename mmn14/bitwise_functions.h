#ifndef BITWISE_FUNCTIONS_H
#define BITWISE_FUNCTIONS_H

#include "memory_table.h"

/* Returns 1 if the i-th bit of num is 1, and 0 otherwise. */
int is_bit_set(word num, int bit_index);

/* Sets the i-th bit of num to value. */
void set_bit(word *num, int bit_index, int value);

/*
Sets the bits of num from start_index_in_num to end_index_in_num to decimal.
start and end are inclusive.
*/
void set_decimal_in_bits(word *num, int decimal, int start_index_in_num, int end_index_in_num);

#endif
