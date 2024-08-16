#include "bitwise_functions.h"
#include "memory_table.h"

int is_bit_set(word num, int bit_index)
{
    return num & (1 << bit_index);
}

/* Sets the i-th bit of num to value. */
void set_bit(word *num, int bit_index, int value)
{
    if (value)
    {
        *num |= (1 << bit_index);
    }
    else
    {
        *num &= ~(1 << bit_index);
    }
}

/*
Sets the bits of num from start_index_in_num to end_index_in_num to decimal.
start and end are inclusive.
*/
void set_decimal_in_bits(word *num, int decimal, int start_index_in_num, int end_index_in_num)
{
    int i;
    for (i = start_index_in_num; i <= end_index_in_num; i++)
    {
        set_bit(num, i, decimal & 1);

        decimal >>= 1;
    }
}
