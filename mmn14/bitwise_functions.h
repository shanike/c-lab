#ifndef BITWISE_FUNCTIONS_H
#define BITWISE_FUNCTIONS_H

#include "global_variables.h"

/* Returns 1 if the i-th bit of num is 1, and 0 otherwise. */
int is_bit_set(word num, int bit_index);

/* Sets the i-th bit of num to value. */
void set_bit(word *num, int bit_index, int value);

/*
Sets the bits of num from start_index_in_num to end_index_in_num according to int.
start and end are inclusive.
*/
void set_bits_from_int(word *num, int decimal, int start_index_in_num, int end_index_in_num);

/* Returns the lower 15 bits of an int */
int get_word_15bits(word num);

#endif
