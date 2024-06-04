#include <stdio.h>
#include "set.h"

void print_ints_until_negative(int *arr)
{
    int i = -1;
    while (*(arr + (++i)) != -1)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void print_string(char *arr)
{
    int i = -1;
    while (*(arr + (++i)) != '\0')
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* UTIL: Reset set.members to 0 */
void reset_set(Set *set)
{
    int i;
    for (i = 0; i < NUM_OF_BYTES; i++)
    {
        ((*set).members)[i] = 0;
    }
}

int is_bit_on(Set *set, int byte_index, int bit_index)
{
    return ((*set).members[byte_index] & (1 << bit_index));
}

int is_bit_off(Set *set, int byte_index, int bit_index)
{
    return !is_bit_on(set, byte_index, bit_index);
}

void turn_bit_on(Set *set, int byte_index, int bit_index)
{
    (*set).members[byte_index] |= 1 << bit_index;
}

/*
Override the set set set`ith `members`,
where `members` is an array of integers,
where the last member is -1.
*/
void read_set(Set *set, int *members)
{
    int i = -1;
    int member, byte_index, bit_index;
    printf("Adding to set...\n");

    reset_set(set);

    /* Register members into set */
    while ((member = members[++i]) != -1)
    {
        byte_index = members[i] / BYTE_SIZE;
        bit_index = members[i] % BYTE_SIZE;
        turn_bit_on(set, byte_index, bit_index);
    }
}

/*
Pretty prints in an ascending order with a max of 16 values per line.
If set is empty prints "The set is empty"
*/
void print_set(Set *set)
{
    int is_empty = 0;
    int byte_i, bit_j;
    for (byte_i = 0; byte_i < NUM_OF_BYTES; byte_i++)
    {
        for (bit_j = 0; bit_j < BYTE_SIZE; bit_j++)
        {
            if (is_bit_on(set, byte_i, bit_j))
            {
                if (is_empty == 0)
                {
                    is_empty = 1;
                    printf("Set { ");
                }
                printf("%d ", byte_i * BYTE_SIZE + bit_j);
            }
        }
    }
    if (is_empty == 0)
    {
        printf("The set is empty\n");
    }
    else
    {
        printf("}\n");
    }
}

/* Unites sets 1 and 2 into set 3 */
void union_set(Set *set1, Set *set2, Set *set3)
{
    int byte_i, bit_j;
    for (byte_i = 0; byte_i < NUM_OF_BYTES; byte_i++)
    {
        for (bit_j = 0; bit_j < BYTE_SIZE; bit_j++)
        {
            if (is_bit_on(set1, byte_i, bit_j) || is_bit_on(set2, byte_i, bit_j))
            {
                turn_bit_on(set3, byte_i, bit_j);
            }
        }
    }
}

/* Intersects sets 1 and 2 into set 3 */
void intersect_set(Set *set1, Set *set2, Set *set3)
{
    int byte_i, bit_j;
    for (byte_i = 0; byte_i < NUM_OF_BYTES; byte_i++)
    {
        for (bit_j = 0; bit_j < BYTE_SIZE; bit_j++)
        {
            if (is_bit_on(set1, byte_i, bit_j) && is_bit_on(set2, byte_i, bit_j))
            {
                turn_bit_on(set3, byte_i, bit_j);
            }
        }
    }
}

/* Subtracts set 2 from 1 into set 3 */
void sub_set(Set *set1, Set *set2, Set *set3)
{
    int byte_i, bit_j;
    for (byte_i = 0; byte_i < NUM_OF_BYTES; byte_i++)
    {
        for (bit_j = 0; bit_j < BYTE_SIZE; bit_j++)
        {
            if (is_bit_on(set1, byte_i, bit_j) && is_bit_off(set2, byte_i, bit_j))
            {
                turn_bit_on(set3, byte_i, bit_j);
            }
        }
    }
}

/* Symetric diff between set 1 and 2 into set 3 */
void symdiff_set(Set *set1, Set *set2, Set *set3)
{
    int byte_i, bit_j;
    for (byte_i = 0; byte_i < NUM_OF_BYTES; byte_i++)
    {
        for (bit_j = 0; bit_j < BYTE_SIZE; bit_j++)
        {
            if (is_bit_on(set1, byte_i, bit_j) != is_bit_on(set2, byte_i, bit_j))
            {
                turn_bit_on(set3, byte_i, bit_j);
            }
        }
    }
}