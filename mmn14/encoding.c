#include <stdio.h>

#include "./validations.h"
#include "./generic_file_functions.h"
#include "./global_variables.h"
#include "./encoding.h"

void print_opcode(op_code *op)
{
    printf("{ \n  name: %s,\n", op->name);
    printf("  arg_number: %d,\n", op->arg_number);
    printf("  code: %d,\n", op->code);
    printf("}\n");
}

/* Prints the bits of a number, left to right. */
void print_bits(word num)
{
    int i;
    for (i = 0; i < BITS_IN_WORD; i++)
    {
        printf("%d", (num & (1 << i)) ? 1 : 0);
    }
    printf("\n");
}

/* Returns 1 if the i-th bit of num is 1, and 0 otherwise. */
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

/* Sets the bits of num from start_index_in_num to end_index_in_num to decimal. */
void set_decimal_in_bits(word *num, int decimal, int start_index_in_num, int end_index_in_num)
{
    int i;
    for (i = start_index_in_num; i <= end_index_in_num; i++)
    {
        set_bit(num, i, decimal & 1);

        decimal >>= 1;
    }
}

int encode_op(op_code *op, char *args_str, location_in_file file_location)
{
    word encoding = 15;
    char *ob_filename;
    FILE *ob_fp; /* ob file pointer */

    if (IS_DEBUG)
    {
        printf("encoding operation: %s\n", op->name);
        printf("arguments: %s\n", args_str);
    }

    /* create file called--> */
    ob_filename = create_new_file(file_location.file_name, OBJECT_FILE_EXT);

    if (!ob_filename)
    {
        return FAILURE;
    }

    if (open_file_for_writing(ob_filename, &ob_fp) == FAILURE)
    {
        return FAILURE;
    }

    set_decimal_in_bits(&encoding, op->code, 11, 14);

    fclose(ob_fp);

    return 0;
}
