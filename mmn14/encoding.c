#include <stdio.h>

#include "./validations.h"
#include "./generic_file_functions.h"
#include "./global_variables.h"
#include "./encoding.h"
#include "./memory_table.h"
#include "./error_handling.h"
#include "./addressing_methods.h"
#include "bitwise_functions.h"
#include "a_r_e_fields.h"

void print_opcode(op_code *op)
{
    printf("{ \n  name: %s,\n", op->name);
    printf("  arg_number: %d,\n", op->arg_number);
    printf("  code: %d,\n", op->code);
    printf("}\n");
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
        printf("%d:%s (l:%ld)", i, array[i], strlen(array[i]));
    }
    printf("\n");
}
void print_array_ints(char *name, int array[], int array_len)
{
    int i;
    printf("%s", name);
    for (i = 0; i < array_len; i++)
    {
        if (i)
        {
            printf(", ");
        }
        printf("%d:%d ", i, array[i]);
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
int encode_op(op_code *op, char *args_str, location_in_file file_location, int *IC, wordNode **memory_table)
{
    word op_word = 0;
    char *ob_filename;
    FILE *ob_fp; /* ob file pointer */

    char **args;
    int args_number = op->arg_number;
    enum addressing_methods addressing_methods[2] = {INVALID, INVALID};
    int i;

    printf("encoding operation %s\n", op->name);

    args = allocate_memory_with_check(args_number * sizeof(char *));
    if (args == NULL)
    {
        return FAILURE;
    }
    /* Reset args elements to NULL: */
    for (i = 0; i < args_number; i++)
    {
        /* TODO NOW check why not set not setting! this makes line 117 and 119 not work which makes an undefined arg to be treated as an invalid addressing method */
        *(args + i) = NULL;
    }

    if (split_args(args_str, args, args_number) != args_number)
    {
        print_file_error(ERROR_STATUS_CODE_119, file_location, args_number);
        return FAILURE;
    }
    print_array("args: ", args, 2);

    set_decimal_in_bits(&op_word, op->code, 11, 14); /* WORKS! */

    if (args[0])
        addressing_methods[0] = find_addressing_method(args[0], file_location);
    if (args[1])
        addressing_methods[1] = find_addressing_method(args[1], file_location);
    print_array_ints("addressing_methods: ", addressing_methods, 2);
    if (addressing_methods[0] == -1 || addressing_methods[1] == -1)
    {
        return FAILURE;
    }
    set_decimal_in_bits(&op_word, addressing_methods[0], 7, 10);
    set_decimal_in_bits(&op_word, addressing_methods[1], 6, 3);

    turn_on_a(&op_word);

    add_node_to_list_word(memory_table, op_word, *IC, op->name);

    print_list_word(*memory_table);

    free(args);

    return SUCCESS;
}
