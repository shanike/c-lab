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

/* UTIL: Reset set.elements to 0 */
void reset_set(SET *set)
{
    int i;
    for (i = 0; i < NUM_OF_BYTES; i++)
    {
        (*set).elements[i] = 0;
    }
}

/*
Override the set set set`ith `elements`,
where `elements` is an array of integers,
where the last element is -1.
*/
void read_set(SET *set, int *elements)
{
    int i = -1;
    int elem, byte_index, bit_index;

    reset_set(set);

    /* Register elements into set */
    while ((elem = elements[++i]) != -1)
    {
        byte_index = elements[i] / BYTE_SIZE;
        bit_index = elements[i] % BYTE_SIZE;
        (*set).elements[byte_index] |= 1 << bit_index;
    }
}

/*
Pretty prints in an ascending order with a max of 16 values per line.
If set is empty prints "The set is empty"
*/
void print_set(SET *set)
{
    int is_empty = 0;
    int byte_i, bit_j;
    for (byte_i = 0; byte_i < NUM_OF_BYTES; byte_i++)
    {
        for (bit_j = 0; bit_j < BYTE_SIZE; bit_j++)
        {
            if (((*set).elements[byte_i] & (1 << bit_j)))
            {
                if (is_empty == 0)
                {
                    printf("{ ");
                }
                is_empty = 1;
                printf("%d ", byte_i * BYTE_SIZE + bit_j);
            }
        }
    }
    printf("}\n");
}

/* Unites sets 1 and 2 into set 3 */
void union_set(SET set1, SET set2, SET set3)
{
    /* TODO */
}

/* Intersects sets 1 and 2 into set 3 */
void intersect_set(SET set1, SET set2, SET set3)
{
    /* TODO */
}

/* Subtracts set 2 from 1 into set 3 */
void sub_set(SET set1, SET set2, SET set3)
{
    /* TODO */
}

/* Symetric diff between set 1 and 2 into set 3 */
void symdiff_set(SET set1, SET set2, SET set3)
{
    /* TODO */
}