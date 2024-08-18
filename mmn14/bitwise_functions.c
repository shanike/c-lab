#include "bitwise_functions.h"

int is_bit_set(word num, int bit_index)
{
    return num & (1 << bit_index);
}

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

void set_bits_from_int(word *num, int int_val, int start_index_in_num, int end_index_in_num)
{
    int i;
    for (i = start_index_in_num; i <= end_index_in_num; i++)
    {
        set_bit(num, i, int_val & 1);

        int_val >>= 1;
    }
}

int get_word_15bits(word num)
{
    return num & 0x7FFF;
}
