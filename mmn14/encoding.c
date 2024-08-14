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

/* TODO temp */
void print_opcode(operation *op)
{
    printf("{ \n  name: %s,\n", op->name);
    printf("  arg_number: %d,\n", op->arg_number);
    printf("  code: %d,\n", op->code);
    printf("}\n");
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
/* TODO temp */
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

/* Returns the addressing method's index in the word encoding. */
int get_arg_encoding_index(enum arg_index arg_index)
{
    if (arg_index == FIRST_ARG)
    {
        return 7;
    }
    else if (arg_index == SECOND_ARG)
    {
        return 3;
    }
}

/*
Returns the number of cells in memory the operation takes.
*/
int encode_op(operation *op, char *args_str, location_in_file file_location, int *IC, wordNode **memory_table)
{
    word op_word = 0;
    char *ob_filename;
    FILE *ob_fp; /* ob file pointer */

    char **args;
    int args_number = op->arg_number, arg_start_index;
    enum addressing_methods curr_addressing_method;
    int i;

    if (IS_DEBUG)
        printf("encoding operation %s\n", op->name);

    args = allocate_memory_with_check(args_number * sizeof(char *));
    if (args == NULL)
    {
        return FAILURE;
    }
    /* Reset args elements to NULL: */
    for (i = 0; i < args_number; i++)
    {
        *(args + i) = NULL;
    }

    if (args_number > MAX_ARGS_NUMBER || split_args(args_str, args, args_number) != args_number)
    {
        print_file_error(ERROR_STATUS_CODE_119, file_location, args_number);
        return FAILURE;
    }

    set_decimal_in_bits(&op_word, op->code, 11, 14);

    if (args_number == 1) /* TODO try to join the two if statements */
    {
        curr_addressing_method = find_addressing_method(args[0], file_location);
        if (IS_DEBUG)
            printf("addressing_method of arg %s: %d\n", args[0], curr_addressing_method);
        if (curr_addressing_method == INVALID)
        {
            return FAILURE;
        }
        arg_start_index = get_arg_encoding_index(SECOND_ARG);
        set_bit(
            &op_word,
            arg_start_index + curr_addressing_method,
            1);
    }
    else
    {
        /* args_number == 2 */
        for (i = 0; i < args_number; i++)
        {
            curr_addressing_method = find_addressing_method(args[i], file_location);
            if (IS_DEBUG)
                printf("addressing_method of arg %s: %d\n", args[i], curr_addressing_method);
            if (curr_addressing_method == INVALID)
            {
                return FAILURE;
            }
            /* args_number is lte MAX_ARGS_NUMBER (=2), so arg_end_index and arg_start_index will not be -1 */
            arg_start_index = get_arg_encoding_index(i);
            set_bit(
                &op_word,
                arg_start_index + curr_addressing_method,
                1);
        }
    }
    turn_on_a(&op_word);

    add_node_to_list_word(memory_table, op_word, *IC, op->name);

    if (IS_DEBUG)
        print_list_word_octal(*memory_table);

    free(args);

    return SUCCESS;
}
