#include <stdio.h>

#include "./validations.h"
#include "./generic_file_functions.h"
#include "./global_variables.h"
#include "./encoding.h"
#include "./memory_table.h"
#include "./error_handling.h"

void print_opcode(op_code *op)
{
    printf("{ \n  name: %s,\n", op->name);
    printf("  arg_number: %d,\n", op->arg_number);
    printf("  code: %d,\n", op->code);
    printf("}\n");
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

/*
Splits a string into an array of strings, using the delimiters ", \t".
Returns the number of strings in the array.
*/
int split_args(char *args_str, char *args[], int args_number)
{
    char delim[] = ", \t";
    char *token = strtok(args_str, delim);
    int i;
    for (i = 0; i < args_number; i++)
    {
        if (token == NULL)
        {
            break;
        }
        args[i] = token;
        token = strtok(NULL, delim);
    }
    return i;
}

/* TODO temp */
void print_array(char *name, char **array, int array_len)
{
    int i;
    printf("%s", name);
    for (i = 0; i < array_len; i++)
    {
        if (i)
        {
            printf(", ");
        }
        printf("%d:%s", i, array[i]);
    }
    printf("\n");
}

/* TODO temp */
void print_encoding(word encoding)
{
    printf("encoding: ");
    print_bits(encoding);
    printf("\nencoding in hex: %04X\n", encoding);
}

/*
Returns the number of cells in memory the operation takes.
*/
int encode_op(op_code *op, char *args_str, location_in_file file_location, int *IC, wordNode *memory_table)
{
    word encoding = 0;
    char *ob_filename;
    FILE *ob_fp; /* ob file pointer */

    char **args;

    printf("encoding operation: %s\n", op->name);

    args = malloc(op->arg_number * sizeof(char *));
    if (split_args(args_str, args, op->arg_number) != op->arg_number)
    {
        print_file_error(ERROR_STATUS_CODE_119, file_location, op->arg_number);
        return FAILURE;
    }
    print_array("args: ", args, op->arg_number);

    set_decimal_in_bits(&encoding, op->code, 11, 14);
    set_decimal_in_bits(&encoding, op->code, 7, 10);

    add_node_to_list_word(memory_table, encoding, *IC, op->name);

    (*IC)++;

    print_encoding(encoding);

    print_list_word(memory_table);

    return SUCCESS;
}
